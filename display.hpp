#ifndef _DISPLAY_HPP
#define _DISPLAY_HPP

#include "board.hpp"

class DisplayBoard{
    Board *board = nullptr;
public:
    DisplayBoard(Board &board);//: board(&board){}
    DisplayBoard()=default;
    void setBoard(Board *myBoard);//{ board = myBoard;}
    void draw();
};


#endif


