#include "ColorSelector.h"
#include "Color.h"
#include <FL/Enumerations.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include "Application.h"
using namespace bobcat;

void ColorSelector::deselectAllColors() {
    redButton->label("");
    orangeButton->label("");
    yellowButton->label("");
    greenButton->label("");
    blueButton->label("");
    indigoButton->label("");
    violetButton->label("");
}

void ColorSelector::visualizeSelectedColor() {
    if (color == RED) {
        redButton->label("@+5square");
    }
    else if (color == ORANGE) {
        orangeButton->label("@+5square");
    }
    else if (color == YELLOW) {
        yellowButton->label("@+5square");
    }
    else if (color == GREEN) {
        greenButton->label("@+5square");
    }
    else if (color == BLUE) {
        blueButton->label("@+5square");
    }
    else if (color == INDIGO) {
        indigoButton->label("@+5square");
    }
    else if (color == VIOLET) {
        violetButton->label("@+5square");
    }
}

void ColorSelector::onClick(bobcat::Widget* sender) {
    deselectAllColors();
    usingCustomColor = false;

    if (sender == redButton) {
        color = RED;
    }
    else if (sender == orangeButton) {
        color = ORANGE;
    }
    else if (sender == yellowButton) {
        color = YELLOW;
    }
    else if (sender == greenButton) {
        color = GREEN;
    }
    else if (sender == blueButton) {
        color = BLUE;
    }
    else if (sender == indigoButton) {
        color = INDIGO;
    }
    else if (sender == violetButton) {
        color = VIOLET;
    }
    //Color Change 
    if (app){
        app->recolorSelected(getColor());
    }
    
    

    visualizeSelectedColor();
    redraw();

}
Color ColorSelector::getColor() const {
    if(usingCustomColor){
        return customColor;
    }
    if (color == RED) {
        return Color(255/255.0, 0/255.0, 0/255.0);
    }
    else if (color == ORANGE) {
        return Color(255/255.0, 127/255.0, 0/255.0);
    }
    else if (color == YELLOW) {
        return Color(255/255.0, 255/255.0, 0/255.0);
    }
    else if (color == GREEN) {
        return Color(0/255.0, 255/255.0, 0/255.0);
    }
    else if (color == BLUE) {
        return Color(0/255.0, 0/255.0, 255/255.0);
    }
    else if (color == INDIGO) {
        return Color(75/255.0, 0/255.0, 130/255.0);
    }
    else if (color == VIOLET) {
        return Color(148/255.0, 0/255.0, 211/255.0);
    }
    else {
        return Color();
    }
}

ColorSelector::ColorSelector(int x, int y, int w, int h) : Group(x, y, w, h) {
    redButton = new Button(x, y, 50, 50, "");
    orangeButton = new Button(x + 50, y, 50, 50, "");
    yellowButton = new Button(x + 100, y, 50, 50, "");
    greenButton = new Button(x + 150, y, 50, 50, "");
    blueButton = new Button(x + 200, y, 50, 50, "");
    indigoButton = new Button(x + 250, y, 50, 50, "");
    violetButton = new Button(x + 300, y, 50, 50, "");

    customButton = new Button(x + 300, y + 50, 50, 50, "C");
    customButton->color(FL_WHITE);
    customButton->labelcolor(FL_BLACK);
    ON_CLICK(customButton, ColorSelector::openColorPopup);
    add(customButton); 

    color = RED;

    redButton->color(fl_rgb_color(255, 0, 0));
    orangeButton->color(fl_rgb_color(255, 127, 0));
    yellowButton->color(fl_rgb_color(255, 255, 0));
    greenButton->color(fl_rgb_color(0, 255, 0));
    blueButton->color(fl_rgb_color(0, 0, 255));
    indigoButton->color(fl_rgb_color(75, 0, 130));
    violetButton->color(fl_rgb_color(148, 0, 211));

    redButton->labelcolor(FL_WHITE);
    orangeButton->labelcolor(FL_WHITE);
    yellowButton->labelcolor(FL_WHITE);
    greenButton->labelcolor(FL_WHITE);
    blueButton->labelcolor(FL_WHITE);
    indigoButton->labelcolor(FL_WHITE);
    violetButton->labelcolor(FL_WHITE);

    visualizeSelectedColor();

    ON_CLICK(redButton, ColorSelector::onClick);
    ON_CLICK(orangeButton, ColorSelector::onClick);
    ON_CLICK(yellowButton, ColorSelector::onClick);
    ON_CLICK(greenButton, ColorSelector::onClick);
    ON_CLICK(blueButton, ColorSelector::onClick);
    ON_CLICK(indigoButton, ColorSelector::onClick);
    ON_CLICK(violetButton, ColorSelector::onClick);
}
// This shit sucks to implement 
void ColorSelector::openColorPopup(bobcat::Widget*) { 
    if (!popup) {
        popup = new Fl_Window(250, 200, "Choose Color");

        redSlider = new Fl_Slider(20,20,200,20,"R");
        redSlider->type(FL_HOR_NICE_SLIDER); 
        redSlider->bounds(0,255); 
        redSlider->value(128);
        
        greenSlider = new Fl_Slider(20,60,200,20,"G");
        greenSlider->type(FL_HOR_NICE_SLIDER); greenSlider->bounds(0,255); greenSlider->value(128);
        
        blueSlider = new Fl_Slider(20,100,200,20,"B");
        blueSlider->type(FL_HOR_NICE_SLIDER); blueSlider->bounds(0,255); blueSlider->value(128);

        previewBox = new Fl_Box(20, 140, 50 ,30);
        previewBox -> box(FL_FLAT_BOX);
        previewBox -> color(fl_rgb_color(128,128,128));
        //Had to look this part up 
        auto apply = new Fl_Button(150,140,80,30,"Apply");
        apply->callback([](Fl_Widget*, void* data){
            auto* self = static_cast<ColorSelector*>(data);
            int r = self->redSlider->value();
            int g = self->greenSlider->value();
            int b = self->blueSlider-> value();
            self->customColor = Color(r / 255.0, g / 255.0, b / 255.0);
            self->usingCustomColor = true;
            self->popup->hide();
            self->deselectAllColors(); 
            self->redraw();
            auto updatePreview = [](Fl_Widget*, void* data){
                auto* self = static_cast<ColorSelector*>(data);
                int r = self->redSlider->value();
                int g = self->greenSlider->value();
                int b = self->blueSlider-> value();
                self->previewBox->color(fl_rgb_color(r,g,b));
                self->previewBox->redraw();
            };
        }, this);
    

    auto updatePreview = [](Fl_Widget*, void* data){
        auto* self = static_cast<ColorSelector*>(data);
        int r = self->redSlider->value();
        int g = self->greenSlider->value();
        int b = self->blueSlider-> value();
        self->previewBox->color(fl_rgb_color(r,g,b));
        self->previewBox->redraw();
    };

    redSlider->callback(updatePreview, this);
    greenSlider->callback(updatePreview, this);
    blueSlider->callback(updatePreview, this);

    popup->end();
    }
    popup->show();



}

    void ColorSelector::updatePreviewColor(){
        int r = redSlider->value();
        int g = greenSlider->value();
        int b = blueSlider->value();
        previewBox->color(fl_rgb_color(r,g,b));
        previewBox->redraw();
 }
        //Static wrapper fix 
    void ColorSelector::previewCallback(Fl_Widget*,void* data){
        auto* self = static_cast<ColorSelector*>(data);
        self->updatePreviewColor();
   
    }
    
