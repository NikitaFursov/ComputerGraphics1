#define GLEW_DLL
#define GLFW_DLL
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "Shader.h"

float points[] = {
    -0.5f, -0.5, -0.0f, // 0
     0.5f, -0.5f, 0.0f, // 1
     0.0f, 0.5f, 0.0f, // 2
};

GLuint index[] = {
    0, 1, 2, 
    0, 2, 1, 
};

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3.\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(512, 512, "Mainwindow", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Error initializing GLEW: %s\n", glewGetErrorString(glewInit()));
        return -1;
    }

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader("vertex_shader.glsl", "fragment_shader.glsl");

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();

        float redValue = (sin(timeValue) / 2) + 0.5; 
        float greenValue = (cos(timeValue) / 2) + 0.5; 
        float blueValue = (sin(timeValue + 3.14) / 2) + 0.5; 

        shader.Use();
        shader.SetUniform("ourColor", redValue, greenValue, blueValue, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0); 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    const GLubyte* version_str = glGetString(GL_VERSION);
    const GLubyte* device_str = glGetString(GL_RENDERER);

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("This version OpenGL running is %s\n", version_str);
    printf("This device OpenGL running is %s\n", device_str);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}