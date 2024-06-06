#ifndef CIRCLE_H
#define CIRCLE_H

#include <GLFW/glfw3.h>

class Circle {
public:
    static void draw(float cx, float cy, float r, int num_segments);
    static void drawWithOutline(float cx, float cy, float r, int num_segments, float outlineWidth, float rotationAngle);
};

#endif // CIRCLE_H
