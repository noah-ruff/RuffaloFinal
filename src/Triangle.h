#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Draw.h"
#include <GL/gl.h>

class Triangle : public Draw{
    private:
    float x,y;
    Color color;


public:
    Triangle(float x, float y, const Color& color);

    void draw()const override;
    bool hitTest(float x, float y) const override;
    void move(float dx, float dy) override;
    void resize(float dx, float dy)  override;
    void setColor(const Color& c) override;
};
#endif