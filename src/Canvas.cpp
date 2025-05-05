#include "Canvas.h"
#include "Circle.h"
#include "Triangle.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "scrib.h"

#include <algorithm>

#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <GL/freeglut.h>
#include <cmath>
#include <cstddef>
#include "Draw.h"


#include <GL/gl.h>
//OVerhauling each add method to use Draw* in order to store scrib 
// Have to remove shape and point Entirely because I chose to make my own scrib 


// Accidently Fixed a lecture material instea so I paste here
Canvas::Canvas(int x, int y, int w, int h) : Canvas_(x, y, w, h) {
    mode(FL_RGB | FL_ALPHA | FL_DOUBLE);
    box(FL_BORDER_BOX);
}

void Canvas::addDrawable(Draw* d) {
    drawables.push_back(d);
}


void Canvas::addPoint(float x, float y, float r, float g, float b, int size) {
    auto* scrib = new Scrib(Color(r,g,b), size);
    scrib->addPoint(x,y);
    addDrawable(scrib);
}

void Canvas::addRectangle(float x, float y, float r, float g, float b) {
    addDrawable(new Rectangle(x, y, r, g, b));
}

void Canvas::addCircle(float x, float y, float r, float g, float b) {
    addDrawable(new Circle(x, y, r, g, b));
}

void Canvas::addTriangle(float x, float y, float r, float g, float b) {
    addDrawable(new Triangle(x,y,Color(r,g,b)));
}

void Canvas::addPolygon(float x, float y, float r, float g, float b) {
    addDrawable(new Polygon(x,y,Color(r,g,b)));
}

void Canvas::clear() {
    for (auto* d : drawables)
    delete d;
drawables.clear();
selected = nullptr;
}

void Canvas::draw() {
    glViewport(0,0,w(),h());

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w(),h(),0);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    for(auto* d : drawables)
        d->draw();

}

void Canvas::selectAt(float x, float y){
    selected = nullptr;
    for (auto it = drawables.rbegin(); it != drawables.rend(); ++it){
        if ((*it)->hitTest(x,y)){
            selected = *it;
            break;
        }
    }
}

void Canvas::render() {
    draw();
}

Draw* Canvas::hitTest(float x, float y){
    for (int i = drawables.size()-1; i >= 0; --i){
        if (drawables[i] ->hitTest(x,y)){
            return drawables[i];
        }
    }
    return nullptr;
}
//Fuck it we just doin reorder

void Canvas::bringToFront(Draw* d) {
    auto it = std::find(drawables.begin(), drawables.end(), d);
    if (it != drawables.end()){
        drawables.erase(it);
        drawables.push_back(d);
    }
}

void Canvas::sendToBack(Draw* d){
    auto it = std::find(drawables.begin(), drawables.end(), d);
    if (it != drawables.end()){
        drawables.erase(it);
        drawables.insert(drawables.begin(), d);
    }
}