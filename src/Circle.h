#ifndef CIRCLE_H
#define CIRCLE_H
#include"Draw.h"

class Circle : public Draw{
    float x;
    float y;
    float radius;
    float r;
    float g;
    float b;

public:
    Circle();
    Circle(float x, float y, float r, float g, float b);
    void draw()const override;
    bool hitTest(float x, float y) const override;
    void move(float dx, float dy) override;
    void resize(float dx, float dy)  override;
    void setColor(const Color& c) override;
};

#endif