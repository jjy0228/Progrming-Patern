#ifndef STAR_H
#define STAR_H

#include <GLFW/glfw3.h>

class Star {
public:
    static void draw(float cx, float cy, float outerRadius, float innerRadius, int spikes, float starRotation);
    static void drawWithOutline(float cx, float cy, float outerRadius, float innerRadius, int spikes, float starRotation);
};

#endif // STAR_H
