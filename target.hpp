#ifndef _TARGET_HPP
#define _TARGET_HPP

#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>

#include "rectangle.hpp"

class Target{
    Point pos;
    int boxSize;
    Rectangle target;

    void copyFromOther(const Target &other){
        pos = other.pos;
        boxSize = other.boxSize;
        target = other.target;
    }

public:
    Target (Point center={0,0}, int boxSize=10): pos(center), boxSize(boxSize), target(center, boxSize, boxSize, FL_BLACK, FL_RED){}
    Target(const Target  &other){
        copyFromOther(other);
    }

    Target &operator=(const Target &copy){
        copyFromOther(copy);
        return *this;
    }

    Point getPosFltk() const {return pos;}
    int getSize()const {return boxSize;}

    void setPos(int x, int y){ pos.x = x; pos.y = y;}
    void draw();
    Rectangle &getRectangle(){ return target;}
    void setTargetColor(){target.setFillColor(FL_MAGENTA);}


};

#endif
