#ifndef _BOX_HPP
#define _BOX_HPP


#include "rectangle.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>

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
    Box (Point center={100,100}, int boxSize=50): pos(center), boxSize(boxSize), box(center, boxSize, boxSize, FL_WHITE, FL_YELLOW){}
    Box(const Box  &other){
        copyFromOther(other);
    }

    Box &operator=(const Box &copy){
        copyFromOther(copy);
        return *this;
    }

    Point getPos() const {return pos;}

    //void setPos(int x, int y){ pos.x = x; pos.y = y;}
    void draw();


};

#endif
