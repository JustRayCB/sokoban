#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP

#include "board.hpp"

class Controll{
    Board *board = nullptr;

public:
    void setBoard(Board *myBoard);//{ board = myBoard;}
                                  
    void movePlayer(int keyCode);
    void moveBox(int keyCode, int boxPosX, int boxPosY);
    void move(int keyCode);

    void boxTargetToEmpty(GameObject &box);

    //Possible moves with a box
    void emptyPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    void emptyPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    void emptyPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    void emptyPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    void targetPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    
    //Possible moves without a box
    void emptyPlayerToEmpty(int keyCode);
    void emptyPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    void targetPlayerToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    

};



#endif
