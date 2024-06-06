#include "Star.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Star::draw(float cx, float cy, float outerRadius, float innerRadius, int spikes, float starRotation) {
    float rot = M_PI / 2 * 3;
    float step = M_PI / spikes;

    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glRotatef(-starRotation, 0, 0, 1);

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 0);
    for (int i = 0; i <= spikes * 2; i++) {
        float r = (i % 2 == 0) ? outerRadius : innerRadius;
        float x = r * cosf(rot);
        float y = r * sinf(rot);
        glVertex2f(x, y);
        rot += step;
    }
    glEnd();

    glPopMatrix();
}

void Star::drawWithOutline(float cx, float cy, float outerRadius, float innerRadius, int spikes, float starRotation) {
    glColor3ub(0, 0, 0);
    draw(cx, cy, outerRadius + 0.01, innerRadius + 0.01, spikes, starRotation);

    glColor3ub(255, 242, 0);
    draw(cx, cy, outerRadius, innerRadius, spikes, starRotation);
}
