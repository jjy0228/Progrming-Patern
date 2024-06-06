#include "Ellipse.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Ellipse::draw(float cx, float cy, float rx, float ry, int num_segments, float angle) {
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glRotatef(angle, 0, 0, 1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
}
