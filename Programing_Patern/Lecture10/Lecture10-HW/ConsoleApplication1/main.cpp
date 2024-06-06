#include <GLFW/glfw3.h>
#include "Circle.h"
#include "Ellipse.h"
#include "EarthAndStar.h"
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void render(GLFWwindow* window) {
    static float earthRevolution = 0.0;
    static float earthRotation = 0.0;
    static float sunRotation = 0.0;
    static float starRevolution = 0.0;
    static float starRotation = 0.0;

    const float earthRevolutionSpeed = 360.0 / 60.0;
    const float earthRotationSpeed = 360.0 / 10.0;
    const float sunRotationSpeed = 360.0 / 5.0;
    const float starRevolutionSpeed = 360.0 / 3.0;
    const float starRotationSpeed = 360.0 / 3.0;

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    Circle::drawWithOutline(0.0, 0.0, 0.3, 360, 2.0, sunRotation);
    EarthAndStar::draw(earthRevolution * M_PI / 180.0, 0.7, 0.1, starRevolution * M_PI / 180.0, starRotation, earthRotation);

    glPopMatrix();
    glfwSwapBuffers(window);

    earthRevolution += earthRevolutionSpeed * glfwGetTime();
    earthRotation += earthRotationSpeed * glfwGetTime();
    sunRotation += sunRotationSpeed * glfwGetTime();
    starRevolution += starRevolutionSpeed * glfwGetTime();
    starRotation += starRotationSpeed * glfwGetTime();
    glfwSetTime(0.0);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Solar System Animation", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window\n";
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        render(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
