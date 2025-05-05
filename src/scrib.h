#ifndef SCRIB_H
#define SCRIB_H
#include <GL/freeglut.h>
#include "Draw.h"
#include <vector>
#include <utility> 

class Scrib : public Draw {
    private: 
        std::vector<std::pair<float,float>> points;
        Color color;
        float radius;

    public:
        Scrib(const Color& color, float radius); 


        void addPoint(float x, float y){
            points.emplace_back(x,y);
        }

        void draw() const override;
        bool hitTest(float x, float y) const override;
        void move(float dx, float dy) override;
        void resize(float dx, float dy) override;
        void setColor(const Color& c) override;
        
};
#endif