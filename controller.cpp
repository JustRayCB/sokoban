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
    int xPlayerVector = board->getPosX(), yPlayerVector = board->getPosY();
    if (keyCode == FL_Right or keyCode == 'd') {
        if (board->isInBoard(xPlayerVector, yPlayerVector+1) and not board->isWall(xPlayerVector, yPlayerVector+1)){
            if (board->isBox(xPlayerVector, yPlayerVector+1) and board->isInBoard(xPlayerVector, yPlayerVector+2)  and (board->isEmpty(xPlayerVector, yPlayerVector+2) or board->isTarget(xPlayerVector, yPlayerVector+2))) {
                // déplacement vers la droite avec box
                if (board->isTarget(xPlayerVector, yPlayerVector+2)) {
                    // on est sur une cible
                    GameObject *tmp = &board->getElem(xPlayerVector, yPlayerVector+1);
                    tmp->setColor(FL_MAGENTA);
                }
                this->moveBox(keyCode, xPlayerVector, yPlayerVector+1);
                this->movePlayer(keyCode);
            }
            else if (not board->isBox(xPlayerVector, yPlayerVector+1)) {
                // déplacement vers la droite sans box
                this->movePlayer(keyCode);
            }
        }else {
            // déplacement vers la droite impossible
            std::cout << "You shall not pass" << std::endl;
        }

    }else if (keyCode == FL_Left or keyCode == 'q') {
        if (board->isInBoard(xPlayerVector, yPlayerVector-1) and not board->isWall(xPlayerVector, yPlayerVector-1)){
            if (board->isBox(xPlayerVector, yPlayerVector-1) and board->isInBoard(xPlayerVector, yPlayerVector-2)  and (board->isEmpty(xPlayerVector, yPlayerVector-2) or board->isTarget(xPlayerVector, yPlayerVector-2))) {
                // déplacement vers la gauche avec box
                if (board->isTarget(xPlayerVector, yPlayerVector-2)) {
                    // on est sur une cible
                       GameObject *tmp = &board->getElem(xPlayerVector, yPlayerVector-1);
                    tmp->setColor(FL_MAGENTA);
                }
                this->moveBox(keyCode, xPlayerVector, yPlayerVector-1);
                this->movePlayer(keyCode);
            }
            else if (not board->isBox(xPlayerVector, yPlayerVector-1)) {
                // déplacement vers la gauche sans box
                this->movePlayer(keyCode);
            }

        }else {
        std::cout << "You shall not pass" << std::endl;
        }

    }else if (keyCode == FL_Up or keyCode == 'z') {
        if (board->isInBoard(xPlayerVector-1, yPlayerVector) and not board->isWall(xPlayerVector-1, yPlayerVector)){
            if (board->isBox(xPlayerVector-1, yPlayerVector) and board->isInBoard(xPlayerVector-2, yPlayerVector)  and (board->isEmpty(xPlayerVector-2, yPlayerVector) or board->isTarget(xPlayerVector-2, yPlayerVector))) {
                // déplacement vers le haut avec box
                if (board->isTarget(xPlayerVector-2, yPlayerVector)) {
                    // on est sur une cible
                    GameObject *tmp = &board->getElem(xPlayerVector-1, yPlayerVector);
                    tmp->setColor(FL_MAGENTA);
                }
                this->moveBox(keyCode, xPlayerVector-1, yPlayerVector);
                this->movePlayer(keyCode);
            }
            else if (not board->isBox(xPlayerVector-1, yPlayerVector)) {
                // déplacement vers le haut sans box
                this->movePlayer(keyCode);
            }

        }else {
        std::cout << "You shall not pass" << std::endl;
        }


    }else if (keyCode == FL_Down or keyCode == 's') {
        if (board->isInBoard(xPlayerVector+1, yPlayerVector) and not board->isWall(xPlayerVector+1, yPlayerVector)){
            if (board->isBox(xPlayerVector+1, yPlayerVector) and board->isInBoard(xPlayerVector+2, yPlayerVector)  and (board->isEmpty(xPlayerVector+2, yPlayerVector) or board->isTarget(xPlayerVector+2, yPlayerVector))) {
                // déplacement vers le bas avec box
                if (board->isTarget(xPlayerVector+2, yPlayerVector)) {
                    // on est sur une cible
                    GameObject *tmp = &board->getElem(xPlayerVector+1, yPlayerVector);
                    tmp->setColor(FL_MAGENTA);
                }
                this->moveBox(keyCode, xPlayerVector+1, yPlayerVector);
                this->movePlayer(keyCode);
            }
            else if (not board->isBox(xPlayerVector+1, yPlayerVector)) {
                // déplacement vers le bas sans box
                this->movePlayer(keyCode);
            }
        }else {
        std::cout << "You shall not pass" << std::endl;
        }
    }

}
