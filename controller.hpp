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

};



#endif
