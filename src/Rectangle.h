#ifndef RECTANGLE_H
#define RECTANGLE_H


#include "Draw.h"

class Rectangle :  public Draw {
    float x;
    float y;
    float width;
    float height;
    float r;
    float g;
    float b;

public:
    Rectangle();
    Rectangle(float x, float y, float r, float g, float b);
    void draw()const override;
    bool hitTest(float x, float y) const override;
    void move(float dx, float dy) override;
    void resize(float dx, float dy)  override;
    void setColor(const Color& c) override;
    
};

#endif