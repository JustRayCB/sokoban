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

    int xIdx = board->getPosX(), yIdx = board->getPosY();
    int boxSize = board->getElem(xIdx, yIdx).getSize();
    bool isPlayerMovable = board->isInBoard(xIdx+deltaX, yIdx+deltaY) 
                        and not board->isWall(xIdx+deltaX, yIdx+deltaY);
    if (isPlayerMovable){
        if (board->isBox(xIdx+deltaX, yIdx+deltaY) and board->isInBoard(xIdx+2*deltaX, yIdx+2*deltaY)  
                and (board->isEmpty(xIdx+2*deltaX, yIdx+2*deltaY) 
                    or board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY))) {
            // déplacement avec box
            if (board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                // on est sur une cible
                board->getElem(xIdx+deltaX, yIdx+deltaY).setColor(FL_MAGENTA);
                board->setOnTarget({xIdx+2*deltaX, yIdx+2*deltaY}, true);
            }
            this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
            this->movePlayer(keyCode);
            if (board->wasOnTarget({xIdx+deltaX, yIdx+deltaY}, true)) {
                //si une box était sur une cible
                board->getElem(xIdx+2*deltaX, yIdx+2*deltaY).setColor(FL_YELLOW);
                board->setOnTarget({xIdx+deltaX, yIdx+deltaY}, false);
            } else if (board->wasOnTarget({xIdx, yIdx}, false)) {
                GameObject target{{200+yIdx*boxSize, 200+xIdx*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xIdx, yIdx, target);
            }
            board->incrementStepCount();
        }
        else if (not board->isBox(xIdx+deltaX, yIdx+deltaY)) {
            // déplacement sans box
            if (board->isTarget(xIdx+deltaX, yIdx+deltaY)) {
                // on arrive sur une cible
                board->setOnTarget(Point{xIdx+deltaX, yIdx+deltaY}, false);
            }
            this->movePlayer(keyCode);
            if (board->wasOnTarget({xIdx, yIdx}, false)) {
                //si on était sur une cible
                GameObject target{{200+yIdx*boxSize, 200+xIdx*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xIdx, yIdx, target);
            }
            board->incrementStepCount();
        }
    }else {
        // déplacement impossible
        std::cout << "You shall not pass" << std::endl;
    }
}
