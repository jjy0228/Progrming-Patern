#include <GLFW/glfw3.h>
#include <iostream>
#pragma comment(lib, "Opengl32.lib")

float scale = 0.1f;
float starX = 0.0f;
float starY = 0.0f;
bool isDragging = false;
double prevX, prevY;

void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        prevX = mouseX;
        prevY = mouseY;
        isDragging = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        isDragging = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        prevX = mouseX;
        prevY = mouseY;
        isDragging = true;
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        isDragging = false;
    }
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (isDragging)
    {
        double deltaX = xpos - prevX;
        double deltaY = ypos - prevY;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {         
            starX += deltaX * scale;
            starY -= deltaY * scale;
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {        
            double scaleFactor = 1.0 + (deltaX - deltaY) * 0.01;

            scale *= scaleFactor;
        }

        prevX = xpos;
        prevY = ypos;
    }
}

void render()
{
    glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 1.0f, 1.0f); 

    glVertex2f((0.0f + starX) * scale, (0.8f + starY) * scale);
    glVertex2f((0.2f + starX) * scale, (0.3f + starY) * scale);
    glVertex2f((-0.2f + starX) * scale, (0.3f + starY) * scale);

    glVertex2f((0.0f + starX) * scale, (0.3f + starY) * scale);
    glVertex2f((0.7f + starX) * scale, (0.3f + starY) * scale);
    glVertex2f((0.4f + starX) * scale, (-0.2f + starY) * scale);

    glVertex2f((0.4f + starX) * scale, (-0.2f + starY) * scale);
    glVertex2f((0.0f + starX) * scale, (-0.2f + starY) * scale);
    glVertex2f((0.5f + starX) * scale, (-0.8f + starY) * scale);

    glVertex2f((-0.4f + starX) * scale, (-0.2f + starY) * scale);
    glVertex2f((0.0f + starX) * scale, (-0.2f + starY) * scale);
    glVertex2f((-0.5f + starX) * scale, (-0.8f + starY) * scale);

    glVertex2f((0.0f + starX) * scale, (0.3f + starY) * scale);
    glVertex2f((-0.7f + starX) * scale, (0.3f + starY) * scale);
    glVertex2f((-0.4f + starX) * scale, (-0.2f + starY) * scale);

    glVertex2f((0.0f + starX) * scale, (0.3f + starY) * scale);
    glVertex2f((0.4f + starX) * scale, (-0.2f + starY) * scale);
    glVertex2f((-0.4f + starX) * scale, (-0.2f + starY) * scale);

    glEnd();
}

int main(void)
{
    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
