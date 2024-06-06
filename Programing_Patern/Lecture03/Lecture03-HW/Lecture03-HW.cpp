#include <iostream>

enum ForeColour {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

void drawObject(int colorCode) {
    std::cout << "\x1b[" << colorCode << "m";
    std::cout << "▣";
}

int main() {
    std::cout << "게임콘텐츠 학과 프로그래밍 패턴 3주차 과제" << std::endl;
    std::cout << "화면에 그림을 그리는 프로그램입니다." << std::endl;
    std::cout << "학번 : 202027057" << std::endl;
    std::cout << "이름 : 장준영" << std::endl << std::endl; 

    int objectCode;

    while (true) {
        std::cout << "\n화면에 그릴 물체코드를 입력하세요 (프로그램 종료: 64) :"; 
        std::cin >> objectCode;

        if (objectCode == 64)
            break;

        if (objectCode < ForeColour::Default || objectCode > ForeColour::White) {
            std::cout << "잘못된 숫자를 입력하셨습니다." << std::endl;
            continue; 
        }

        drawObject(objectCode);
    }
    
    return 0;
}
