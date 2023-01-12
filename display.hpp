#ifndef _DISPLAY_HPP
#define _DISPLAY_HPP

#include <FL/fl_message.H>

#include "board.hpp"


class DisplayBoard{
    Board *board = nullptr;
public:
    DisplayBoard(Board &board);//: board(&board){}
    DisplayBoard()=default;
    void setBoard(Board *myBoard);//{ board = myBoard;}
    void drawCells(); //function tha will draw all cells in the gameBoard vector
    void displayTxt(); //function that will draw the text
    void displayLegend();
    void draw(); //main draw function
};


#endif


