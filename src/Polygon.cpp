#include "Polygon.h"
#include <cmath>

Polygon::Polygon(float x,float y, const Color& color, int sides, float radius)
: x(x), y(y), radius(radius), color(color), sides(sides){}

void Polygon::draw() const { 

    glColor3f(color.getR(),color.getG(),color.getB());

    glBegin(GL_POLYGON);
    for (int i = 0; i<sides; i++){
        float angle = 2* M_PI * i/sides - M_PI/2;
        float vx = x + cos(angle)* radius;
        float vy = y + sin(angle)* radius;
        glVertex2f(vx,vy);
    }
    glEnd();

}
bool Polygon::hitTest(float mx, float my) const {
    float dx = mx -x;
    float dy = my - y;
    return dx * dx + dy * dy <= radius * radius;
}

void Polygon::move(float dx, float dy){
    x += dx;
    y += dy;
}

void Polygon::resize(float dx, float dy) {
    radius += (dx+dy) * 0.1f;
    if (radius < 5.0f) radius = 5.0f;
}
void Polygon::setColor(const Color& c){
    color = c;
}