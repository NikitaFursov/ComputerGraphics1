//Performed by Fursov N.T. ASUb-23-1
//Option 19
//Shape: Triangle, Shape color: (0.3,1.0,1.0), Background color: (1.0,1.0,1.0)
#define GLEW_DLL
#define GLFW_DLL
#include <glew.h>
#include <glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3.\n");
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(512, 512, "Window", NULL, NULL);

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

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLE_FAN);

        glColor3f(0.3f, 1.0f, 1.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);

        glEnd();

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