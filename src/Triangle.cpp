#include "Triangle.h"
#include <cmath>

Triangle::Triangle(float x,float y, const Color& color)
: x(x), y(y), color(color){}

void Triangle::draw() const { 

    glColor3f(color.getR(),color.getG(),color.getB());

    glBegin(GL_TRIANGLES);
        glVertex2f(x, y -20);
        glVertex2f(x-20, y +20);
        glVertex2f(x+20, y +20);
    glEnd();

}
bool Triangle::hitTest(float mx, float my) const {
    return (mx >= x-20 && mx <= x+20 && my >= y-20 && my <= y+20);
}

void Triangle::move(float dx, float dy){
    x += dx;
    y += dy;
}

void Triangle::resize(float dx, float dy) {

}
void Triangle::setColor(const Color& c){
    color =c;
}