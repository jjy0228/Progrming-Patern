#include <GLFW/glfw3.h>
#include <iostream>
#pragma comment(lib, "Opengl32.lib")

float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    if ((button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_LEFT) && action == GLFW_PRESS)
    {
        if (xpos > 0 && xpos < width && ypos > 0 && ypos < height)
        {
            if (button == GLFW_MOUSE_BUTTON_RIGHT)
            {
                clearColor[0] = 1.0f;
                clearColor[1] = 0.0f;
                clearColor[2] = 0.0f;
            }
            else if (button == GLFW_MOUSE_BUTTON_LEFT)
            {
                clearColor[0] = 0.0f;
                clearColor[1] = 1.0f;
                clearColor[2] = 0.0f;
            }
        }
    }
    else if ((button == GLFW_MOUSE_BUTTON_RIGHT || button == GLFW_MOUSE_BUTTON_LEFT) && action == GLFW_RELEASE)
    {
        clearColor[0] = 0.0f;
        clearColor[1] = 0.0f;
        clearColor[2] = 0.0f;
    }
}

void MouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && xpos > 0 && xpos < width && ypos > 0 && ypos < height)
    {
        clearColor[0] = 0.0f;
        clearColor[1] = 0.0f;
        clearColor[2] = 1.0f;
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && xpos > 0 && xpos < width && ypos > 0 && ypos < height)
    {
        clearColor[0] = 1.0f;
        clearColor[1] = 0.0f;
        clearColor[2] = 1.0f;
    }
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 768, "MuSeounEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, MouseMoveCallback);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
