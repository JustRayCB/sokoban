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
    if (keyCode == FL_Up or keyCode == 'z') {
        deltaX--;
    }else if (keyCode == FL_Left or keyCode == 'q') {
        deltaY--;
    }else if (keyCode == FL_Down or keyCode == 's') {
        deltaX++;
    }else if (keyCode == FL_Right or keyCode == 'd') {
        deltaY++;
    }
    int xPlayerVector = board->getPosX(), yPlayerVector = board->getPosY();
    if (board->isInBoard(xPlayerVector+deltaX, yPlayerVector+deltaY) and not board->isWall(xPlayerVector+deltaX, yPlayerVector+deltaY)){
        if (board->isBox(xPlayerVector+deltaX, yPlayerVector+deltaY) and board->isInBoard(xPlayerVector+2*deltaX, yPlayerVector+2*deltaY)  
                and (board->isEmpty(xPlayerVector+2*deltaX, yPlayerVector+2*deltaY) 
                    or board->isTarget(xPlayerVector+2*deltaX, yPlayerVector+2*deltaY))) {
            // déplacement avec box
            if (board->isTarget(xPlayerVector+2*deltaX, yPlayerVector+2*deltaY)) {
                // on est sur une cible
                board->getElem(xPlayerVector+deltaX, yPlayerVector+deltaY).setColor(FL_MAGENTA);
            }
            this->moveBox(keyCode, xPlayerVector+deltaX, yPlayerVector+deltaY);
            this->movePlayer(keyCode);
        }
        else if (not board->isBox(xPlayerVector+deltaX, yPlayerVector+deltaY)) {
            // déplacement sans box
            if (board->isTarget(xPlayerVector+deltaX, yPlayerVector+deltaY)) {
                // on est sur une cible
                board->setOnTarget(Point{xPlayerVector+deltaX, yPlayerVector+deltaY});
            }
            std::cout << "Avant :" <<"(" << xPlayerVector << "," << yPlayerVector << ")" << std::endl;
            GameObject *tmp = &board->getElem(xPlayerVector, yPlayerVector);
            std::cout << "avant 2: "<<  "(" << tmp->getPosFltk().x << "," << tmp->getPosFltk().y << ")" << std::endl;
            this->movePlayer(keyCode);
            std::cout << "avant 3: "<<  "(" << tmp->getPosFltk().x << "," << tmp->getPosFltk().y << ")" << std::endl;
            if (board->wasOnTarget({xPlayerVector, yPlayerVector})) {
                //si on était sur une cible
                std::cout << "TRUE" << std::endl;
                
                std::cout << "après 2: "<<  "(" << tmp->getPosFltk().x << "," << tmp->getPosFltk().y << ")" << std::endl;
                tmp->setColor(FL_MAGENTA);
                tmp->setName("target");
                tmp->setSize(tmp->getSize() / 2);

                // board->setObject(xPlayerVector, yPlayerVector, tmp);
            }
        }
    }else {
        // déplacement impossible
        std::cout << "You shall not pass" << std::endl;
    }
    board->displayTargetsPosition();
    board->displayTargetsBool();


}
