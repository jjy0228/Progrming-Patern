#ifndef EARTHANDSTAR_H
#define EARTHANDSTAR_H

#include <GLFW/glfw3.h>

class EarthAndStar {
public:
    static void draw(float earthAngle, float earthDistance, float earthSize, float starRevolutionAngle, float starRotationAngle, float earthRotationAngle);
};

#endif // EARTHANDSTAR_H
