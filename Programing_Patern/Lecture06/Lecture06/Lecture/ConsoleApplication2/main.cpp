#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include "Star.h"
#include "MSList.h"
#include "MObject.h"

float moveFactor = 0.0f;
float scaleFactor = 1.0f;

void errorCallback(int error, const char* description) {
    std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

MSList<Star*> stars;  



int initialize() {
    srand(static_cast<unsigned int>(time(nullptr)));  
    // 별 객체 생성 및 리스트에 추가
    for (int i = 0; i < 300; ++i) {
        float randomX = ((float(rand()) / RAND_MAX) * 20.0f - 10.0f) * 2.0f; 
        float randomY = (float(rand()) / RAND_MAX) * 2.0f - 1.0f;  
        stars.add(new Star(randomX, randomY));
    }

    return 0;
}
int release() {
    for (int i = 0; i < stars.size(); ++i) {
        delete stars.get(i);
    }
    stars.clear(); 
    return 0;
}

int update() {
    float deltaTime = 0.016;  
    for (int i = 0; i < stars.size(); ++i) {
        stars.get(i)->update(deltaTime);  
    }
    return 0;
}

int render() {
    glClearColor(0.1f, 0.2f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < stars.size(); ++i) {
        stars.get(i)->render();
    }
    return 0;
}

int main(void) {
    if (!glfwInit()) {
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    initialize();
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        update();
        render();
        glfwSwapBuffers(window);
    }
    release();
    glfwTerminate();
    return 0;
}
