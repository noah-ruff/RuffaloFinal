#ifndef POLYGON_H
#define POLYGON_H

#include "Draw.h"
#include <GL/gl.h>
#include <vector>
#include <cmath>

class Polygon : public Draw{
    private:
    float x,y;
    Color color;
    int sides;
    float radius;


public:
    Polygon(float x, float y, const Color& color, int sides =5, float radius = 20.0f);

    void draw()const override;
    bool hitTest(float x, float y) const override;
    void move(float dx, float dy) override;
    void resize(float dx, float dy)  override;
    void setColor(const Color& c) override;
};
#endif