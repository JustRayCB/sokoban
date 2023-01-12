#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <iostream>
#include <string>

#include "board.hpp"
#include "display.hpp"
#include "rectangle.hpp"
#include "text.hpp"

#define STARTDISPLAYX (800)
#define STARTDISPLAYY (200)

DisplayBoard::DisplayBoard(Board &board): board(&board){
}


void DisplayBoard::setBoard(Board *myBoard){
    board = myBoard;
}

void DisplayBoard::drawCells(){
    for (auto &line : board->getBoard()) {
        for (auto &row : line) {
            row.draw();
        }
    }
}

void DisplayBoard::displayTxt(){
    int target = board->getTargetsCount();
    int stepCount = board->getStepCount();
    int userBestScore = board->getBestScore();
    int userLimit = board->getLimit();

    Text status{{STARTDISPLAYX, STARTDISPLAYY}};
    Text steps{ "steps: "+std::to_string(stepCount), {STARTDISPLAYX, STARTDISPLAYY+50}};
    Text bestScore{ "best score: " + std::to_string(userBestScore), {STARTDISPLAYX, STARTDISPLAYY+100}};
    Text limit{ "Limit: " + std::to_string(userLimit), {STARTDISPLAYX, STARTDISPLAYY+150}};
    if (target == board->getTotalTargets()){
        status.setString("You won !!");
        Text remain{std::to_string(board->getLimit()-board->getStepCount()) + 
                " steps remaining", {STARTDISPLAYX, STARTDISPLAYY+200}};
        remain.draw();
    } 
    else if (board->isGameOver()) {
        status.setString("You Loose !!");
    }
    else {
        status.setString("targets: "+std::to_string(target)+"/"+std::to_string(board->getTotalTargets()));
    }
    status.draw(); steps.draw(); bestScore.draw(); limit.draw();
}

void DisplayBoard::displayLegend(){
    Rectangle player({STARTDISPLAYX, STARTDISPLAYY+260}, 20, 20, FL_BLACK, FL_GREEN);
    Text txtPlayer("Player", {STARTDISPLAYX+15, STARTDISPLAYY+270});
    Rectangle box({STARTDISPLAYX, STARTDISPLAYY+285}, 20, 20, FL_BLACK, FL_YELLOW);
    Text txtBox("Boxes", {STARTDISPLAYX+15, STARTDISPLAYY+295});
    Rectangle target({STARTDISPLAYX, STARTDISPLAYY+310}, 20, 20, FL_BLACK, FL_MAGENTA);
    Text txtTarget("Targets", {STARTDISPLAYX+15, STARTDISPLAYY+320});
    Rectangle tp({STARTDISPLAYX, STARTDISPLAYY+335}, 20, 20, FL_BLACK, FL_CYAN);
    Text txtTp("Tps", {STARTDISPLAYX+15, STARTDISPLAYY+345});
    Rectangle wall({STARTDISPLAYX, STARTDISPLAYY+360}, 20, 20, FL_BLACK, FL_BLUE);
    Text txtWall("Walls", {STARTDISPLAYX+15, STARTDISPLAYY+370});
    player.draw(); box.draw(); target.draw(); tp.draw(); wall.draw();
    txtPlayer.draw(); txtBox.draw(); txtTarget.draw(); txtTp.draw(); txtWall.draw();

}
void DisplayBoard::draw(){
    drawCells();
    displayTxt();
    displayLegend();
}


