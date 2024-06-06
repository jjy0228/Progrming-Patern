#include "EarthAndStar.h"
#include "Star.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void EarthAndStar::draw(float earthAngle, float earthDistance, float earthSize, float starRevolutionAngle, float starRotationAngle, float earthRotationAngle) {
    float earthX = earthDistance * cosf(earthAngle);
    float earthY = earthDistance * sinf(earthAngle);

    glColor3ub(0, 0, 0);
    glPushMatrix();
    glTranslatef(earthX, earthY, 0.0);
    glRotatef(earthAngle * (180 / M_PI), 0.0, 0.0, 1.0);
    glRotatef(earthRotationAngle, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-earthSize / 2 - 0.01, -earthSize / 2 - 0.01);
    glVertex2f(earthSize / 2 + 0.01, -earthSize / 2 - 0.01);
    glVertex2f(earthSize / 2 + 0.01, earthSize / 2 + 0.01);
    glVertex2f(-earthSize / 2 - 0.01, earthSize / 2 + 0.01);
    glEnd();

    glColor3ub(91, 155, 213);
    glBegin(GL_QUADS);
    glVertex2f(-earthSize / 2, -earthSize / 2);
    glVertex2f(earthSize / 2, -earthSize / 2);
    glVertex2f(earthSize / 2, earthSize / 2);
    glVertex2f(-earthSize / 2, earthSize / 2);
    glEnd();

    float starX = (earthSize + earthDistance / 4) * cosf(starRevolutionAngle);
    float starY = (earthSize + earthDistance / 4) * sinf(starRevolutionAngle);
    Star::drawWithOutline(starX, starY, earthSize / 3, earthSize / 6, 5, starRotationAngle);

    glPopMatrix();
}
