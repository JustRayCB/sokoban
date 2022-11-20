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
    std::cout << "Pos player before when moving: " << newX << "," << newY << std::endl;
    GameObject *tmp = &board->getElem(newX, newY);
    Point PlayerPos = tmp->getPosFltk();
    int boxSize = tmp->getSize();
    if (keyCode == FL_Right or keyCode == 'd') {
        std::cout << "Move to the  right" << std::endl;
        newY++;
        tmp->setPos(PlayerPos.x + boxSize, PlayerPos.y);
    }else if (keyCode == FL_Left or keyCode == 'q') {
        newY--;
        std::cout << "Move to the  left" << std::endl;
        tmp->setPos(PlayerPos.x - boxSize, PlayerPos.y);
    }else if (keyCode == FL_Up or keyCode == 'z') {
        newX--;
        std::cout << "Move up" << std::endl;
        tmp->setPos(PlayerPos.x, PlayerPos.y - boxSize);
    }else if (keyCode == FL_Down or keyCode == 's') {
        newX++;
        std::cout << "Move down" << std::endl;
        tmp->setPos(PlayerPos.x, PlayerPos.y + boxSize);
    }
    std::cout << "Pos player after when moving: " << newX << "," << newY << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    tmp->getRectangle().setCenter(tmp->getPosFltk());
    board->movePlayerInVector(newX, newY);
    
}


void Controll::moveBox(int keyCode, int boxPosX, int boxPosY){
    int oldX = boxPosX, oldY = boxPosY;
    std::cout << "Pos box before when moving: " << boxPosX << "," << boxPosY << std::endl;
    //Box *tmp = board->getElem(boxPosX, boxPosY).getBox();
    GameObject *tmp = &board->getElem(boxPosX, boxPosY);
    Point BoxPos = tmp->getPosFltk();
    int boxSize = tmp->getSize();

    if (keyCode == FL_Right or keyCode == 'd') {
        std::cout << "Move to the  right" << std::endl;
        boxPosY++;
        tmp->setPos(BoxPos.x + boxSize, BoxPos.y);
    }else if (keyCode == FL_Left or keyCode == 'q') {
        boxPosY--;
        std::cout << "Move to the  left" << std::endl;
        tmp->setPos(BoxPos.x - boxSize, BoxPos.y);
    }else if (keyCode == FL_Up or keyCode == 'z') {
        boxPosX--;
        std::cout << "Move up" << std::endl;
        tmp->setPos(BoxPos.x, BoxPos.y - boxSize);
    }else if (keyCode == FL_Down or keyCode == 's') {
        boxPosX++;
        std::cout << "Move down" << std::endl;
        tmp->setPos(BoxPos.x, BoxPos.y + boxSize);
    }
    std::cout << "Pos box after when moving: " << boxPosX << "," << boxPosY << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
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
            // déplacement vers la droite avec box
            if (board->isTarget(xPlayerVector+2*deltaX, yPlayerVector+2*deltaY)) {
                // on est sur une cible
                GameObject *tmp = &board->getElem(xPlayerVector+deltaX, yPlayerVector+deltaY);
                tmp->setColor(FL_MAGENTA);
            }
            this->moveBox(keyCode, xPlayerVector+deltaX, yPlayerVector+deltaY);
            this->movePlayer(keyCode);
        }
        else if (not board->isBox(xPlayerVector+deltaX, yPlayerVector+deltaY)) {
            // déplacement vers la droite sans box
            this->movePlayer(keyCode);
        }
    }else {
        // déplacement vers la droite impossible
        std::cout << "You shall not pass" << std::endl;
    }


}
