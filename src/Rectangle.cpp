#include "Rectangle.h"
#include <GL/freeglut.h>
#include <cmath>
#include <FL/Enumerations.H>
//this is the first thing Im overhauling to use drawables / scrib to store. changing to float values
// Now I have to change to pixel width / height with open gl
Rectangle::Rectangle() {
    x = 0.0f;
    y = 0.0f;
    width = 40.0f;
    height = 40.0f;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

Rectangle::Rectangle(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    width = 40.0f;
    height = 40.0f;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Rectangle::draw() const{
    glColor3f(r, g, b);
    

    glBegin(GL_POLYGON);
        glVertex2f(x - width/2.0f, y + height/2.0f);
        glVertex2f(x + width/2.0f, y + height/2.0f);
        glVertex2f(x + width/2.0f, y - height/2.0f);
        glVertex2f(x - width/2.0f, y - height/2.0f);
    glEnd();
}

bool Rectangle::hitTest(float mx, float my) const {
    return mx >= (x-width/2.0f) && mx <= (x+ width/2.0f) &&
    my >= (y - height/2.0f) && my <= (y + height/2.0f);
}

void Rectangle::move(float dx, float dy){
    x += dx;
    y += dy;
}

void Rectangle::resize(float dx, float dy){
    width += dx;
    height += dy;
    if (width < 5.0f) width =  5.0f;
    if (height <  5.0f) height =  5.0f;
}

void Rectangle::setColor(const Color& color){
    r = color.getR();
    g = color.getG();
    b = color.getB();
}