#ifndef DRAW_H
#define DRAW_H

#include "Color.h"

class Draw {
    public:
        virtual ~Draw() = default;
        bool selected= false;
        void setSelected(bool sel) { selected = sel;}
        bool isSelected() const { return selected;}

        virtual void draw() const = 0;

        //For the Damn Selector
        virtual bool hitTest(float x, float y) const = 0;

        virtual void move(float dx, float dy) = 0;

        virtual void resize(float dx, float dy) = 0;

        virtual void setColor(const Color& c) = 0;
    
};

#endif