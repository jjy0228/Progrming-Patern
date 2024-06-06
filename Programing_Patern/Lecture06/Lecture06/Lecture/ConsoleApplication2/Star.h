#ifndef STAR_H
#define STAR_H

#include <GL/gl.h>
#include <cstdlib>  
#include <ctime>

class Star {
public:
    Star(float x = 0.0f, float y = 0.0f, float scale = 1.0f)
        : starX(x), starY(y), scale(scale), dx(0.0f), dy(1.5f) {
    }

    void update(float deltaTime) {
       
        float dy = -3.0f; 

        starY += dy * deltaTime;
     
        if (starY < -5.0f) {
            starY = 5.0f;  
        }
    }



    void render() {
        glBegin(GL_TRIANGLES);
        float time = glfwGetTime(); 
        float red = sin(time * 0.5f) * 0.5f + 0.5f;
        float green = sin(time * 0.5f + 1.0f) * 0.5f + 0.5f; 
        float blue = sin(time * 0.5f + 2.0f) * 0.5f + 0.5f; 

        float orange = red * 0.9f + green * 0.5f;
        float purple = red * 0.5f + blue * 0.9f;
        float cyan = green * 0.5f + blue * 0.9f;

        if (time < 1.0f) {
            glColor3f(red, green, blue); 
        }
        else if (time < 2.0f) {
            glColor3f(orange, orange * 0.6f, 0.0f); 
        }
        else if (time < 3.0f) {
            glColor3f(purple, 0.0f, purple); 
        }
        else if (time < 4.0f) {
            glColor3f(0.0f, green, 0.0f); 
        }
        else if (time < 5.0f) {
            glColor3f(0.0f, 0.0f, blue); 
        }
        else if (time < 6.0f) {
            glColor3f(0.0f, cyan, cyan); 
        }
        else {
            glColor3f(purple, 0.0f, purple); 
        }


        glVertex2f((0.0f + starX) * scale * 0.2f, (0.8f + starY) * scale * 0.2f);
        glVertex2f((0.2f + starX) * scale * 0.2f, (0.3f + starY) * scale * 0.2f);
        glVertex2f((-0.2f + starX) * scale * 0.2f, (0.3f + starY) * scale * 0.2f);

        glVertex2f((0.0f + starX) * scale * 0.2f, (0.3f + starY) * scale * 0.2f);
        glVertex2f((0.7f + starX) * scale * 0.2f, (0.3f + starY) * scale * 0.2f);
        glVertex2f((0.4f + starX) * scale * 0.2f, (-0.2f + starY) * scale * 0.2f);

        glVertex2f((0.4f + starX) * scale * 0.2f, (-0.2f + starY) * scale * 0.2f);
        glVertex2f((0.0f + starX) * scale * 0.2f, (-0.2f + starY) * scale * 0.2f);
        glVertex2f((0.5f + starX) * scale * 0.2f, (-0.8f + starY) * scale * 0.2f);

        glVertex2f((-0.4f + starX) * scale * 0.2f, (-0.2f + starY) * scale * 0.2f);
        glVertex2f((0.0f + starX) * scale * 0.2f, (-0.2f + starY) * scale * 0.2f);
        glVertex2f((-0.5f + starX) * scale * 0.2f, (-0.8f + starY) * scale * 0.2f);

        glVertex2f((0.0f + starX) * scale * 0.2f, (0.3f + starY) * scale * 0.2f);
        glVertex2f((-0.7f + starX) * scale * 0.2f, (0.3f + starY) * scale * 0.2f);
        glVertex2f((-0.4f + starX) * scale * 0.2f, (-0.2f + starY) * scale * 0.2f);

        glVertex2f((0.0f + starX) * scale * 0.2f, (0.3f + starY) * scale * 0.2f);
        glVertex2f((0.4f + starX) * scale * 0.2f, (-0.2f + starY) * scale * 0.2f);
        glVertex2f((-0.4f + starX) * scale * 0.2f, (-0.2f + starY) * scale * 0.2f);


        glEnd();
    }

private:
    float starX, starY, scale;
    float dx, dy;  
};

#endif 
