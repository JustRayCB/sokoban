#ifndef _WALL_HPP
#define _WALL_HPP


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
    Wall (Point center={100,100}, int boxSize=50): pos(center), boxSize(boxSize), wall(center, boxSize, boxSize, FL_BLACK, FL_BLACK){}
    Wall(const Wall  &other){
        copyFromOther(other);
    }

    Wall &operator=(const Wall &copy){
        copyFromOther(copy);
        return *this;
    }

    Point getPos() const {return pos;}

    //void setPos(int x, int y){ pos.x = x; pos.y = y;}
    void draw();


};

#endif
