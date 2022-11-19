#ifndef _BOX_HPP
#define _BOX_HPP

#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>

#include "rectangle.hpp"

class Box{
    Point pos;
    int boxSize;
    Rectangle box;

    void copyFromOther(const Box &other){
        pos = other.pos;
        boxSize = other.boxSize;
        box = other.box;
    }

public:
    Box (Point center={0,0}, int boxSize=50): pos(center), boxSize(boxSize), box(center, boxSize, boxSize, FL_BLACK, FL_YELLOW){}
    Box(const Box  &other){
        copyFromOther(other);
    }

    Box &operator=(const Box &copy){
        copyFromOther(copy);
        return *this;
    }

    Point getPosFltk() const {return pos;}
    int getSize()const {return boxSize;}

    void setPos(int x, int y){ pos.x = x; pos.y = y;}
    void draw();
    Rectangle &getRectangle(){ return box;}

    void setBoxColor() {box.setFillColor(FL_MAGENTA);}


};

#endif
