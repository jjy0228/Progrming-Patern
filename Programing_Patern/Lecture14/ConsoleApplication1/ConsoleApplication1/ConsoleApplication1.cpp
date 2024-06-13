#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <cstdlib> // rand() 함수를 사용하기 위한 헤더
#include <ctime>   // srand() 함수에 사용되는 시간 헤더
#include <algorithm> // remove_if를 사용하기 위한 헤더

const int WINDOW_WIDTH = 1260;
const int WINDOW_HEIGHT = 800;
const float PIXELS_PER_METER = 100.0f;
const float GRAVITY = -9.8f; // 중력 가속도 (m/s^2)
const float MAX_JUMP_VELOCITY = 5.0f; // 최대 점프 속도 (m/s)
const float MIN_JUMP_VELOCITY = 1.0f; // 최소 점프 속도 (m/s)
const float OBJECT_SPEED = -0.5f; // 물체의 속도 (m/s)
const float OBJECT_SPAWN_INTERVAL = 3.0f; // 물체 생성 간격 (초)
const float MAX_HOLD_TIME = 1.0f; // 최대 점프 시간 (초)

struct Object {
    float posX, posY;
    float width, height;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, bool& isJumping, float& velocityY, bool& isSpacePressed, float& spacePressedTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!isSpacePressed) {
            isSpacePressed = true;
            spacePressedTime = 0.0f;
        }
    }
    else {
        if (isSpacePressed) {
            isSpacePressed = false;
            if (!isJumping) {
                isJumping = true;
                float jumpVelocity = MIN_JUMP_VELOCITY + (MAX_JUMP_VELOCITY - MIN_JUMP_VELOCITY) * std::min(spacePressedTime / MAX_HOLD_TIME, 1.0f);
                velocityY = jumpVelocity;
            }
        }
    }
}

float getRandomHeight() {
    float minHeight = 0.1f * (100.0f / PIXELS_PER_METER); // 최소 높이
    float maxHeight = 0.3f * (100.0f / PIXELS_PER_METER); // 최대 높이
    return minHeight + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxHeight - minHeight)));
}

bool checkCollision(const Object& player, const Object& object) {
    // AABB (Axis-Aligned BoundingBox) 충돌 검사
    return (fabs(player.posX - object.posX) * 2 < (player.width + object.width)) &&
        (fabs(player.posY - object.posY) * 2 < (player.height + object.height));
}

int main() {
    // 랜덤 시드 설정
    srand(static_cast<unsigned int>(time(0)));

    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // GLFW 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Rectangle", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL viewport 설정
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // 물리 시뮬레이션 변수
    float playerPosY = -0.85f; // 플레이어의 초기 y 위치
    float playerVelocityY = 0.0f; // 플레이어의 초기 y 속도
    bool isPlayerJumping = false; // 플레이어가 점프 중인지 여부
    bool isSpacePressed = false; // 스페이스 키가 눌렸는지 여부
    float spacePressedTime = 0.0f; // 스페이스 키가 눌린 시간
    auto previousTime = std::chrono::high_resolution_clock::now();
    auto lastSpawnTime = std::chrono::high_resolution_clock::now();

    std::vector<Object> objects;

    // 플레이어 객체
    Object player = { -0.7f, playerPosY, 0.08f * (100.0f / PIXELS_PER_METER), 0.1f * (100.0f / PIXELS_PER_METER) };

    // 메인 루프
    while (!glfwWindowShouldClose(window)) {
        processInput(window, isPlayerJumping, playerVelocityY, isSpacePressed, spacePressedTime);

        // 시간 업데이트
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsedTime = currentTime - previousTime;
        std::chrono::duration<float> spawnElapsedTime = currentTime - lastSpawnTime;
        previousTime = currentTime;
        float deltaTime = elapsedTime.count();

        // 스페이스 키 누르는 시간 업데이트
        if (isSpacePressed) {
            spacePressedTime += deltaTime;
        }

        // 중력 가속도 적용
        if (isPlayerJumping) {
            playerVelocityY += GRAVITY * deltaTime;
            player.posY += playerVelocityY * deltaTime;

            // 바닥에 닿으면 점프 중지
            if (player.posY <= -0.85f) {
                player.posY = -0.85f;
                isPlayerJumping = false;
                playerVelocityY = 0.0f;
            }
        }

        // 물체 생성
        if (spawnElapsedTime.count() >= OBJECT_SPAWN_INTERVAL) {
            objects.push_back({ 1.1f, -0.85f, 0.08f * (100.0f / PIXELS_PER_METER), getRandomHeight() });
            lastSpawnTime = currentTime;
        }

        // 물체 이동 및 화면 밖으로 나간 물체 제거
        objects.erase(std::remove_if(objects.begin(), objects.end(), [&](Object& object) {
            object.posX += OBJECT_SPEED * deltaTime;

            // 충돌 검사
            if (checkCollision(player, object)) {
                std::cout << "Collision detected! Exiting..." << std::endl;
                glfwSetWindowShouldClose(window, true);
            }

            // 화면 밖으로 나간 물체를 제거
            return object.posX < -1.1f;
            }), objects.end());

        // 배경 색상 설정 및 초기화 (검은색)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 단위 행렬 로드
        glLoadIdentity();

        // 플레이어 사각형 그리기 (흰색)
        glPushMatrix();
        glTranslatef(player.posX, player.posY, 0.0f);

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f); // 흰색
        glVertex2f(-player.width / 2, -player.height / 2); // 왼쪽 아래
        glVertex2f(player.width / 2, -player.height / 2);  // 오른쪽 아래
        glVertex2f(player.width / 2, player.height / 2);   // 오른쪽 위
        glVertex2f(-player.width / 2, player.height / 2);  // 왼쪽 위
        glEnd();

        glPopMatrix();

        // 물체 그리기 (파란색)
        for (const auto& object : objects) {
            glPushMatrix();
            glTranslatef(object.posX, object.posY, 0.0f);

            glBegin(GL_QUADS);
            glColor3f(0.0f, 0.0f, 1.0f); // 파란색
            glVertex2f(-object.width / 2, -object.height / 2); // 왼쪽 아래
            glVertex2f(object.width / 2, -object.height / 2);  // 오른쪽 아래
            glVertex2f(object.width / 2, object.height / 2);   // 오른쪽 위
            glVertex2f(-object.width / 2, object.height / 2);  // 왼쪽 위
            glEnd();

            glPopMatrix();
        }

        // 바닥 그리기 (회색)
        float floorHeight = -1.0f; // 바닥의 y 위치 (화면의 아랫부분에 위치하도록)
        float floorWidth = 1.0f;   // 바닥의 너비

        glBegin(GL_QUADS);
        glColor3f(0.5f, 0.5f, 0.5f); // 회색
        glVertex2f(-floorWidth, floorHeight); // 왼쪽 아래
        glVertex2f(floorWidth, floorHeight);  // 오른쪽 아래
        glVertex2f(floorWidth, floorHeight + 0.1f);   // 오른쪽 위
        glVertex2f(-floorWidth, floorHeight + 0.1f);  // 왼쪽 위
        glEnd();

        // 버퍼 교체
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
