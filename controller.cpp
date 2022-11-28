#include <FL/Enumerations.H>
#include <iostream>

#include "controller.hpp"
#include "board.hpp"
#include "gameObject.hpp"


void Controll::setBoard(Board *myBoard){
    board = myBoard;
}


void Controll::movePlayer(int keyCode){
    int newX = board->getPosX(), newY = board->getPosY();
    GameObject *tmp = &board->getElem(newX, newY);
    const Point playerPosFltk = tmp->getPosFltk();
    const int boxSize = tmp->getSize();
    int deltaX = 0, deltaY = 0;
    if (keyCode == FL_Up or keyCode == 'z') {newX--; deltaY-=boxSize;}
    else if (keyCode == FL_Left or keyCode == 'q') {newY--; deltaX-=boxSize;}
    else if (keyCode == FL_Down or keyCode == 's') {newX++; deltaY+=boxSize;}
    else if (keyCode == FL_Right or keyCode == 'd') {newY++; deltaX+=boxSize;}

    tmp->setPos(playerPosFltk.x + deltaX, playerPosFltk.y+deltaY);
    tmp->getRectangle().setCenter(tmp->getPosFltk());
    board->movePlayerInVector(newX, newY);
}


void Controll::moveBox(int keyCode, int boxPosX, int boxPosY){
    const int oldX = boxPosX, oldY = boxPosY;
    GameObject *tmp = &board->getElem(boxPosX, boxPosY);
    const Point boxPosFltk = tmp->getPosFltk();
    const int boxSize = tmp->getSize();
    int deltaX = 0, deltaY = 0;
    if (keyCode == FL_Up or keyCode == 'z') {boxPosX--; deltaY-=boxSize;}
    else if (keyCode == FL_Left or keyCode == 'q') {boxPosY--; deltaX-=boxSize;}
    else if (keyCode == FL_Down or keyCode == 's') {boxPosX++; deltaY+=boxSize;}
    else if (keyCode == FL_Right or keyCode == 'd') {boxPosY++; deltaX+=boxSize;}

    tmp->setPos(boxPosFltk.x+deltaX, boxPosFltk.y+deltaY);
    tmp->getRectangle().setCenter(tmp->getPosFltk());
    board->movBoxInVector(boxPosX, boxPosY, oldX, oldY);
}
    


void Controll::move(int keyCode){
    /*
     * z -> deltaX = -1, deltaY = 0
     * q -> deltaX = 0, deltaY = -1 
     * s -> deltaX = +1, deltaY = 0
     * d -> deltaX = 0, deltaY = +1
     */
    int deltaX = 0, deltaY = 0;

    if (keyCode == FL_Up or keyCode == 'z') {deltaX--;}
    else if (keyCode == FL_Left or keyCode == 'q') {deltaY--;}
    else if (keyCode == FL_Down or keyCode == 's') {deltaX++;}
    else if (keyCode == FL_Right or keyCode == 'd') {deltaY++;}
    else {return;}

    int xPlayer = board->getPosX(), yPlayer = board->getPosY();
    int boxSize = board->getElem(xPlayer, yPlayer).getSize();
    bool isPlayerMovable = board->isInBoard(xPlayer+deltaX, yPlayer+deltaY) 
                        and not board->isWall(xPlayer+deltaX, yPlayer+deltaY);
    if (isPlayerMovable){
        if (board->isBox(xPlayer+deltaX, yPlayer+deltaY) and board->isInBoard(xPlayer+2*deltaX, yPlayer+2*deltaY)  
                and (board->isEmpty(xPlayer+2*deltaX, yPlayer+2*deltaY) 
                    or board->isTarget(xPlayer+2*deltaX, yPlayer+2*deltaY))) {
            // déplacement avec box
            if (board->isTarget(xPlayer+2*deltaX, yPlayer+2*deltaY)) {
                // on est sur une cible
                board->getElem(xPlayer+deltaX, yPlayer+deltaY).setColor(FL_MAGENTA);
                board->setOnTarget({xPlayer+2*deltaX, yPlayer+2*deltaY}, true);
            }
            this->moveBox(keyCode, xPlayer+deltaX, yPlayer+deltaY);
            this->movePlayer(keyCode);
            if (board->wasOnTarget({xPlayer+deltaX, yPlayer+deltaY}, true)) {
                //si une box était sur une cible
                board->getElem(xPlayer+2*deltaX, yPlayer+2*deltaY).setColor(FL_YELLOW);
                board->setOnTarget({xPlayer+deltaX, yPlayer+deltaY}, false);
            } else if (board->wasOnTarget({xPlayer, yPlayer}, false)) {
                GameObject target{{200+yPlayer*boxSize, 200+xPlayer*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xPlayer, yPlayer, target);
            }
            board->incrementStepCount();
        }
        else if (not board->isBox(xPlayer+deltaX, yPlayer+deltaY)) {
            // déplacement sans box
            if (board->isTarget(xPlayer+deltaX, yPlayer+deltaY)) {
                // on arrive sur une cible
                board->setOnTarget(Point{xPlayer+deltaX, yPlayer+deltaY}, false);
            }
            this->movePlayer(keyCode);
            if (board->wasOnTarget({xPlayer, yPlayer}, false)) {
                //si on était sur une cible
                GameObject target{{200+yPlayer*boxSize, 200+xPlayer*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xPlayer, yPlayer, target);
            }
            board->incrementStepCount();
        }
    }else {
        // déplacement impossible
        std::cout << "You shall not pass" << std::endl;
    }
}
