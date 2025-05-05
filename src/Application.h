#ifndef APPLICATION_H
#define APPLICATION_H

#include "scrib.h"
#include <bobcat_ui/all.h>
#include <bobcat_ui/bobcat_ui.h>
#include "Toolbar.h"
#include "Canvas.h"
#include "ColorSelector.h"

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Toolbar* toolbar;
    Canvas* canvas;
    

    Scrib* currentScribble = nullptr;

    Draw* selected = nullptr;
    Draw* getSelected() const {return selected;}
    Canvas* getCanvas() const {return canvas;}

    bool dragging = false;
    float dragStartX, dragStartY;

    ColorSelector* colorSelector;
    bobcat::Button* openRGBButton;
    bobcat::Button* resizeUpButton;
    bobcat::Button* resizeDownButton;
    void onCanvasMouseUp(bobcat::Widget* sender, float mx, float my);
    void onCanvasMouseDown(bobcat::Widget* sender, float mx, float my);
    void onCanvasDrag(bobcat::Widget* sender, float mx, float my);
    void onToolbarChange(bobcat::Widget* sender);
    void onOpenRGBClicked(bobcat::Widget* sender);
    

public:
    Application();
    void recolorSelected(const Color& c);
    friend struct AppTest;
};


#endif