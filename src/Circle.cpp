#include "Circle.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>


Circle::Circle() {
    x = 0.0f;
    y = 0.0f;
    radius = 0.2f;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

Circle::Circle(float x, float y, float r, float g, float b) 
    : x(x) , y(y), r(r), g(g), b(b), radius(20.0f) {}


void Circle::draw() const{
    glColor3f(r, g, b);

    float inc = M_PI / 32;
    glBegin(GL_POLYGON);
        for (float theta = 0; theta <= 2 * M_PI; theta += inc){
            glVertex2d(x + cos(theta) * radius, y + sin(theta) * radius);
        }
    glEnd();
}

// hit test and shit taken from rect.h had to convert  
bool Circle::hitTest(float mx, float my) const {
    float dx = mx - x;
    float dy =  my -y;
    return(dx * dx + dy * dy <= radius * radius);
}

void Circle::move(float dx, float dy){
    x += dx;
    y += dy;
}

void Circle::resize(float dx, float dy){
    radius += (dx + dy) * 0.1f;
    if (radius < 0.01f) radius = 0.01f;
}
void Circle::setColor(const Color& c) {
    r = c.getR();
    g = c.getG();
    b = c.getB();
}