#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include <FL/Fl_Slider.H>
#include <FL/Fl_Widget.H>
#include <bobcat_ui/all.h>
#include <bobcat_ui/bobcat_ui.h>
#include "Color.h"
#include "Enums.h"
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
class Application;
class ColorSelector : public bobcat::Group {
    bobcat::Button* redButton;
    bobcat::Button* orangeButton;
    bobcat::Button* yellowButton;
    bobcat::Button* greenButton;
    bobcat::Button* blueButton;
    bobcat::Button* indigoButton;
    bobcat::Button* violetButton;

    bobcat::Button* customButton;
    Fl_Window* popup = nullptr;
    Fl_Slider* redSlider = nullptr;
    Fl_Slider* greenSlider = nullptr;
    Fl_Slider* blueSlider = nullptr;
    Fl_Box* previewBox = nullptr;

    Color customColor;
    bool usingCustomColor = false;

    COLOR color;


    void deselectAllColors();
    void visualizeSelectedColor();
    
    void updatePreviewColor();

    static void previewCallback(Fl_Widget*, void* data);
    
    Application* app = nullptr;
public:
    ColorSelector(int x, int y, int w, int h);
    void onClick(bobcat::Widget* sender);
    void openColorPopup(bobcat::Widget* sender);
    Color getColor() const;
    void setApplication(Application* a) {app = a; }

};


#endif