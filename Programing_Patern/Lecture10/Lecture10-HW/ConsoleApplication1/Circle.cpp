#include "Circle.h"
#include "Ellipse.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void Circle::draw(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void Circle::drawWithOutline(float cx, float cy, float r, int num_segments, float outlineWidth, float rotationAngle) {
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glRotatef(rotationAngle, 0, 0, 1);

    glColor3ub(197, 90, 17);
    glLineWidth(outlineWidth);
    Circle::draw(0, 0, r + 0.01, num_segments);

    glColor3ub(255, 217, 102);
    Circle::draw(0, 0, r, num_segments);

    glColor4ub(255, 230, 153, 204);
    Circle::draw(-r / 2, 0, r / 3, num_segments);

    glColor3ub(255, 192, 0);
    Ellipse::draw(r / 2, -r / 2, r / 12, r / 6, num_segments, -45.0f);

    glPopMatrix();
}
