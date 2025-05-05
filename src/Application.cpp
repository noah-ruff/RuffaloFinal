#include "Application.h"
#include "Enums.h"
#include <bobcat_ui/button.h>

using namespace bobcat;
using namespace std;

void Application::onCanvasMouseDown(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    std::cout<< "Mouse down at: " << mx << " , " << my << std::endl;
//After debug I have to convert to pixel cords
    int px = (mx*0.5+0.5)*canvas->w();
    int py = (1.0-(my*0.5+0.5))*canvas->h();

    if (tool == PENCIL) {
        currentScribble = new Scrib(color, 7);
        currentScribble->addPoint(px,py);
    }
    else if (tool == ERASER) {
        canvas->addPoint(px, py, 1.0, 1.0, 1.0, 14);
        canvas->redraw();
    }
    else if (tool == RECTANGLE) {
        canvas->addRectangle(px, py, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == CIRCLE) { 
        canvas->addCircle(px, py, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == TRIANGLE) {
        canvas->addTriangle(px, py, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == POLYGON) {
        canvas->addPolygon(px, py, color.getR(), color.getG(), color.getB());
        canvas->redraw();
    }
    else if (tool == MOUSE){
        selected = canvas->hitTest(px,py);
        if (selected){
            dragging = true;
            dragStartX = px;
            dragStartY= py;
        }
    }

}

void Application::onCanvasMouseUp(bobcat::Widget* sender, float mx, float my){
    TOOL tool = toolbar->getTool();
    dragging = false;
    if (tool == PENCIL && currentScribble){
        canvas->addDrawable(currentScribble);
        currentScribble=nullptr;
        canvas->redraw();
    }
}

void Application::onCanvasDrag(bobcat::Widget* sender, float mx, float my) {
    TOOL tool = toolbar->getTool();
    Color color = colorSelector->getColor();

    int px = (mx*0.5+0.5)*canvas->w();
    int py = (1.0-(my*0.5+0.5))*canvas->h();

    
    if (tool == PENCIL && currentScribble){
        currentScribble->addPoint(px,py);
        canvas->redraw();
    }
    else if (tool == ERASER) {
        canvas->addPoint(px, py, 1.0, 1.0, 1.0, 14);
        canvas->redraw();
    }
    else if (tool == MOUSE && dragging &&  selected){
        float dx = px - dragStartX;
        float dy = py - dragStartY;
        selected->move(dx,dy);
        dragStartX = px;
        dragStartY = py;
        canvas->redraw();
    }
}

void Application::onToolbarChange(bobcat::Widget* sender) {
    ACTION action = toolbar->getAction();

    if (action == CLEAR) {
        canvas->clear();
        canvas->redraw();
    }
    else if (action == BRING_TO_FRONT && selected){
        canvas->bringToFront(selected);
        canvas->redraw();
    }
    else if (action == SEND_TO_BACK && selected){
        canvas->sendToBack(selected);
        canvas->redraw();
    }
    toolbar->clearAction();
}

void Application::onOpenRGBClicked(bobcat::Widget* sender) {
    colorSelector->openColorPopup(nullptr);
}

Application::Application() {
    window = new Window(25, 75, 500, 400, "Final");
    // custom rgb
    


    toolbar = new Toolbar(0, 0, 100, 400);
    canvas = new Canvas(100, 0, 400, 350);


    openRGBButton = new bobcat::Button(0,350,50,30,"RGB");
    colorSelector = new ColorSelector(50, 350, 350, 50);

    bobcat::Button* resizeUpButton;
    bobcat::Button* resizeDownButton;

    colorSelector->box(FL_BORDER_BOX);

    resizeUpButton = new Button(50,80,20,20,"+");
    resizeDownButton = new Button(75,80,20,20,"-");

    window->add(resizeUpButton);
    window->add(resizeDownButton);
    window->add(openRGBButton);
    window->add(toolbar);
    window->add(canvas);
    window->add(colorSelector);


    resizeUpButton->callback([](Fl_Widget*, void* data){
        auto* app = static_cast<Application*>(data);
        if(app->selected){
            app->selected->resize(5,5);
            app->canvas->redraw();
        }else{
            std::cout<<"No shape selected.\n";
        }

    }, this);

    resizeDownButton->callback([](Fl_Widget*, void* data){
        auto* app = static_cast<Application*>(data);
        if(app->selected){
            app->selected->resize(-5,-5);
            app->canvas->redraw();
        }else{
            std::cout<<"No shape selected.\n";
        }

    }, this);


    
    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CLICK(openRGBButton, Application::onOpenRGBClicked);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);

    window->show();
}
    void Application::recolorSelected(const Color& c){
        if (selected){
            selected->setColor(c);
            canvas->redraw();
        }
    }



