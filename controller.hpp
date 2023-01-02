#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP

#include "board.hpp"
#include <string>

class Controll{
    Board *board = nullptr;

public:
    void setBoard(Board *myBoard);//{ board = myBoard;}
                                  
    void movePlayer(int keyCode);
    void tpPlayer(int x, int y);
    void moveBox(int keyCode, int boxPosX, int boxPosY);
    void move(int keyCode);

    void setDeltas(int &keycode, int &xVector, int &yVector, int &deltaX, 
        int &deltaY, const int &boxSize, std::string &move);
    void boxTargetToEmpty(GameObject &box);

    //Possible moves with a box
    void emptyPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    
    //Possible moves without a box
    void emptyPlayerToEmpty(const Point &position, int keyCode, int boxSize);
    void emptyPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerToEmpty(const Point &position, int keyCode, int boxSize);
    void targetPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    

};



#endif
