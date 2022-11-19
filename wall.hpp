#ifndef _WALL_HPP
#define _WALL_HPP

#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>

#include "rectangle.hpp"

class Wall{
    Point pos;
    int boxSize;
    Rectangle wall;

    void copyFromOther(const Wall &other){
        pos = other.pos;
        boxSize = other.boxSize;
        wall = other.wall;
    }

public:
    Wall (Point center={0,0}, int boxSize=50): pos(center), boxSize(boxSize), wall(center, boxSize, boxSize, FL_WHITE, FL_BLUE){}
    Wall(const Wall  &other){
        copyFromOther(other);
    }

    Wall &operator=(const Wall &copy){
        copyFromOther(copy);
        return *this;
    }

    Point getPosFltk() const {return pos;}

    void draw();


};

#endif
