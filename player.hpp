#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>
#include <memory>

#include "rectangle.hpp"

class Player{
    Point pos;
    int boxSize;
    Rectangle player;

    void copyFromOther(const Player &other){
        pos = other.pos;
        boxSize = other.boxSize;
        player = other.player;
    }

public:
    Player(Point center={0,0}, int boxSize=50): pos(center), boxSize(boxSize), player(center, boxSize, boxSize){}
    Player(const Player &other){
        copyFromOther(other);
    }
    
    Player &operator=(const Player &copy){
        copyFromOther(copy);
        return *this;
    }

    Point getPosFltk() const {return pos;}
    int getSize()const {return boxSize;}

    void setPos(int x, int y){ pos.x = x; pos.y = y;}
    void draw();
    Rectangle &getRectangle(){ return player;}


};

#endif
