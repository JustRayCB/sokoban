#include <iostream>

#include "board.hpp"
#include "display.hpp"

DisplayBoard::DisplayBoard(Board &board): board(&board){
}


void DisplayBoard::setBoard(Board *myBoard){
    board = myBoard;
}


void DisplayBoard::draw(){
    for (auto &line : board->getBoard()) {
        for (auto &row : line) {
            if (row.getName() != "empty") {
                row.draw(); 
            }
        }
    }
}


