#include "scrib.h"
#include <GL/gl.h>
#include <cmath> 

Scrib::Scrib(const Color& color, float radius)
: color(color), radius(radius){}



void Scrib::draw() const{
    glColor3f(color.getR(), color.getG(), color.getB());
    glPointSize(radius);
    glBegin(GL_POINTS);
    for (const auto& p : points){
        glVertex2f(p.first, p.second);
    }
    glEnd();
}

bool Scrib::hitTest(float x, float y) const{
    for (const auto& p : points) {
        float dx = p.first  - x;
        float dy = p.second - y;
        if (dx * dx+dy * dy<= radius * radius)
            return true;
    }
    return false;
}

void Scrib::move(float dx, float dy){
    for (auto& p : points){
        p.first += dx;
        p.second += dy;
    }
}

void Scrib::resize(float dx, float dy){
    radius += (dx + dy) * 0.1f;
    if (radius < 1.0f) radius = 1.0f;
}

void Scrib::setColor(const Color& c){
    color = c;
}