#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Shape.h"
#include "Draw.h"
#include <vector>

class Canvas : public bobcat::Canvas_ {
    std::vector<Point*> points;
    std::vector<Shape*> shapes;
    std::vector<Draw*> drawables;
    Draw* selected = nullptr;

public:
    Canvas(int x, int y, int w, int h);

    void selectAt(float x, float y);

    void addPoint(float x, float y, float r, float g, float b, int size);

    void addRectangle(float x, float y, float r, float g, float b);

    void addCircle(float x, float y, float r, float g, float b);

    void clear();


    void addTriangle(float x, float y, float r, float g, float b);

    void addPolygon(float x, float y, float r, float g, float b);
    // Attempting setup Draw and Scrib below
    void addDrawable(Draw* d);

    Draw* getDrawableAt(float x, float y);
    Draw* getSelected();
    Draw* hitTest(float x, float y);
    void setSelected(Draw* d);
    void draw() override;
    void render() override;
    void bringToFront(Draw* d);
    void sendToBack(Draw* d);

};

#endif