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

    // board->displayTargets();
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
        bool isBoxMovable = board->isBox(xIdx+deltaX, yIdx+deltaY) and board->isInBoard(xIdx+2*deltaX, yIdx+2*deltaY)  
                and (board->isEmpty(xIdx+2*deltaX, yIdx+2*deltaY) 
                    or board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY));
        if (isBoxMovable) {
            // déplacement avec box

            // joueur sur vide, box sur vide, vers cible
            if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                std::cout << "Case: \t1" << std::endl;
                board->setOnTarget(Point{xIdx+2*deltaX, yIdx+2*deltaY}, true);
                std::cout << "J'ajoute une boite (" << xIdx+2*deltaX << "," << yIdx+2*deltaY << ") sur une cible" << std::endl;
                board->getElem(xIdx+deltaX, yIdx+deltaY).setColor(FL_MAGENTA);
                this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
                this->movePlayer(keyCode);
            // joueur sur vide, box sur cible, vers vide
            } 
            else if (not board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                std::cout << "Case:\t2" << std::endl;
                board->getElem(xIdx+deltaX, yIdx+deltaY).setColor(FL_YELLOW);
                board->setOnTarget(Point{xIdx+2*deltaX, yIdx+2*deltaY}, false);
                board->removeFromTarget(Point{xIdx+2*deltaX, yIdx+2*deltaY}, false);
                this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
                this->movePlayer(keyCode);
            }
            // joueur sur vide, box sur cible, vers cible
            else if (not board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                std::cout << "Case:\t3" << std::endl;
                board->setOnTarget(Point{xIdx+2*deltaX, yIdx+2*deltaY}, true);
                board->removeFromTarget(Point{xIdx+deltaX, yIdx+deltaY}, true);
                board->setOnTarget(Point{xIdx+deltaX, yIdx+deltaY}, false);
                this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
                this->movePlayer(keyCode);
            }
            // joueur sur cible, box sur vide, vers vide
            else if (board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                std::cout << "Case:\t4" << std::endl;
                this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
                this->movePlayer(keyCode);
                // on redessine la cible
                GameObject target{{200+yIdx*boxSize, 200+xIdx*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xIdx, yIdx, target);
            }
            // joueur sur cible, box sur vide, vers cible
            else if (board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                std::cout << "Case:\t5" << std::endl;
                board->removeFromTarget(Point{xIdx+deltaX, yIdx+deltaY}, false);
                board->setOnTarget(Point{xIdx+2*deltaX, yIdx+2*deltaY}, true);
                board->getElem(xIdx+deltaX, yIdx+deltaY).setColor(FL_MAGENTA);
                this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
                this->movePlayer(keyCode);
                // on redessine la cible
                GameObject target{{200+yIdx*boxSize, 200+xIdx*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xIdx, yIdx, target);
            }
            // joueur sur cible, box sur cible, vers vide
            else if (board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                std::cout << "Case:\t6" << std::endl;
                board->getElem(xIdx+deltaX, yIdx+deltaY).setColor(FL_YELLOW);
                board->setOnTarget(Point{xIdx+deltaX, yIdx+deltaY}, false);
                board->removeFromTarget(Point{xIdx+2*deltaX, yIdx+2*deltaY}, false);
                this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
                this->movePlayer(keyCode);
                // on redessine la cible
                GameObject target{{200+yIdx*boxSize, 200+xIdx*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xIdx, yIdx, target);
            }
            // joueur sur cible, box sur cible, vers cible
            else if (board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                std::cout << "Case:\t7" << std::endl;
                board->setOnTarget(Point{xIdx+deltaX, yIdx+deltaY}, false);
                board->setOnTarget(Point{xIdx+2*deltaX, yIdx+2*deltaY}, true);
                this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
                this->movePlayer(keyCode);
                // on redessine la cible
                GameObject target{{200+yIdx*boxSize, 200+xIdx*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xIdx, yIdx, target);
            } 
            // joueur sur vide, box sur vide, vers vide
            else if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                this->moveBox(keyCode, xIdx+deltaX, yIdx+deltaY);
                this->movePlayer(keyCode);
            }
            board->incrementStepCount();
        }
        else if (not board->isBox(xIdx+deltaX, yIdx+deltaY)) {
            std::cout << "IM HERE" << std::endl;
            std::cout << "board->isOnTarget({xIdx, yIdx}) = " << board->isOnTarget({xIdx, yIdx}) << std::endl;
            std::cout << "board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) = " << board->isOnTarget({xIdx, yIdx}) << std::endl;


            // joueur sur vide, vers cible
            if (not board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                board->setOnTarget(Point{xIdx+deltaX, yIdx+deltaY}, false);
                this->movePlayer(keyCode);
            }
            // joueur sur cible, vers vide
            else if (board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                this->movePlayer(keyCode);
                GameObject target{{200+yIdx*boxSize, 200+xIdx*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xIdx, yIdx, target);
            }
            // joueur sur cible, vers cible
            else if (board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                board->setOnTarget(Point{xIdx+deltaX, yIdx+deltaY}, false);
                this->movePlayer(keyCode);
                GameObject target{{200+yIdx*boxSize, 200+xIdx*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
                board->setObject(xIdx, yIdx, target);
            }
            // joueur sur vide, vers vide
            else if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                this->movePlayer(keyCode);
            }
            board->incrementStepCount();
        }
    }else {
        // déplacement impossible
        std::cout << "You shall not pass" << std::endl;
    }
}
