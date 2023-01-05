#include <FL/Fl.H>
#include <iostream>
#include <string>

#include "board.hpp"
#include "display.hpp"
#include "gameObject.hpp"
#include "text.hpp"

DisplayBoard::DisplayBoard(Board &board): board(&board){
}


void DisplayBoard::setBoard(Board *myBoard){
    board = myBoard;
}

void DisplayBoard::draw(){
    for (auto &line : board->getBoard()) {
        for (auto &row : line) {
            // if (row.getName() != "empty") {
            //     row.draw(); 
            // }
            row.draw();
        }
    }
    int c = board->getTargetsCount();
    int stepCount = board->getStepCount();

    Text status{{830,200}};
    Text steps{ "steps: "+std::to_string(stepCount), {830, 400}};
    Text bestScore{ "best score: " + std::to_string(board->getBestScore()), {830, 500}};
    Text limit{ "Limit: " + std::to_string(board->getLimit()), {830, 600}};
    if (c == board->getTotalTargets()){
        status.setString("You won !!");
        //if limit != 0
        Text remain{std::to_string(board->getLimit()-board->getStepCount()) + 
                " steps remainings", {850, 300}};
        remain.draw();
    } 
    else if (board->isGameOver()) {
        fl_alert("GAME OVER");
        status.setString("You Loose !!");
    }
    else {
        status.setString("targets: "+std::to_string(c)+"/"+std::to_string(board->getTotalTargets()));
    }
    status.draw(); steps.draw(); bestScore.draw(); limit.draw();
}


