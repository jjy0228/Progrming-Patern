#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <GLFW/glfw3.h>

class Ellipse {
public:
    static void draw(float cx, float cy, float rx, float ry, int num_segments, float angle);
};

#endif // ELLIPSE_H
