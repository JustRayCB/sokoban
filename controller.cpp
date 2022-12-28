#include <FL/Enumerations.H>
#include <iostream>

#include "controller.hpp"
#include "board.hpp"
#include "gameObject.hpp"


void Controll::setBoard(Board *myBoard){
    board = myBoard;
}

void Controll::setDeltas(int &keyCode, int &xVector, int &yVector, int &deltaX, 
        int &deltaY, const int &boxSize, std::string &move){
    if (keyCode == FL_Up or keyCode == 'z') {xVector--; deltaY-=boxSize; move = "up";}
    else if (keyCode == FL_Left or keyCode == 'q') {yVector--; deltaX-=boxSize; move = "left";}
    else if (keyCode == FL_Down or keyCode == 's') {xVector++; deltaY+=boxSize; move = "down";}
    else if (keyCode == FL_Right or keyCode == 'd') {yVector++; deltaX+=boxSize; move = "right";}

}

void Controll::movePlayer(int keyCode){
    int newX = board->getPosX(), newY = board->getPosY();
    GameObject *tmp = &board->getElem(newX, newY);
    const int boxSize = tmp->getSize();
    int deltaX = 0, deltaY = 0; std::string move = "";
    setDeltas(keyCode, newX, newY, deltaX, deltaY, boxSize, move);

    board->movePlayerInVector(newX, newY);
    tmp = &board->getElem(newX, newY);
    tmp->setMove(move);
    tmp->addAnimation();

}


void Controll::moveBox(int keyCode, int boxPosX, int boxPosY){
    const int oldX = boxPosX, oldY = boxPosY;
    GameObject *tmp = &board->getElem(boxPosX, boxPosY);
    //const Point boxPosFltk = tmp->getPosFltk();
    const int boxSize = tmp->getSize();
    int deltaX = 0, deltaY = 0; std::string move = "";
    setDeltas(keyCode, boxPosX, boxPosY, deltaX, deltaY, boxSize, move);

    //tmp->setPosFltk(boxPosFltk.x+deltaX, boxPosFltk.y+deltaY);
    board->movBoxInVector(boxPosX, boxPosY, oldX, oldY);
    tmp = &board->getElem(boxPosX, boxPosY);
    tmp->setMove(move);
    tmp->addAnimation();

}


void Controll::emptyPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
}

void Controll::emptyPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_MAGENTA);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
}

void Controll::emptyPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_YELLOW);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, false);
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
}

void Controll::emptyPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
}

void Controll::targetPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}

void Controll::targetPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_MAGENTA);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}

void Controll::targetPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_YELLOW);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}

void Controll::targetPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}

void Controll::emptyPlayerToEmpty(int keyCode){
    this->movePlayer(keyCode);
}
void Controll::emptyPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->movePlayer(keyCode);
}
void Controll::targetPlayerToEmpty(const Point &position, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    this->movePlayer(keyCode);
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}
void Controll::targetPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->movePlayer(keyCode);
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
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

            // joueur sur vide, box sur vide, vers vide
            if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                emptyPlayerEmptyBoxToEmpty({xIdx, yIdx}, deltaX, deltaY, keyCode);
            }
            // joueur sur vide, box sur vide, vers cible
            else if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                emptyPlayerEmptyBoxToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode);
            // joueur sur vide, box sur cible, vers vide
            } 
            else if (not board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                emptyPlayerTargetBoxToEmpty({xIdx, yIdx}, deltaX, deltaY, keyCode);
            }
            // joueur sur vide, box sur cible, vers cible
            else if (not board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                emptyPlayerTargetBoxToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode);
            }
            // joueur sur cible, box sur vide, vers vide
            else if (board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                targetPlayerEmptyBoxToEmpty({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            }
            // joueur sur cible, box sur vide, vers cible
            else if (board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                targetPlayerEmptyBoxToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            }
            // joueur sur cible, box sur cible, vers vide
            else if (board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                targetPlayerTargetBoxToEmpty({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            }
            // joueur sur cible, box sur cible, vers cible
            else if (board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                targetPlayerTargetBoxToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            } 
            board->incrementStepCount();
        }
        else if (not board->isBox(xIdx+deltaX, yIdx+deltaY)) {
            // joueur sur vide, vers vide
            if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                emptyPlayerToEmpty(keyCode);
            }
            // joueur sur vide, vers cible
            else if (not board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                emptyPlayerToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode);
            }
            // joueur sur cible, vers vide
            else if (board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                targetPlayerToEmpty({xIdx, yIdx}, keyCode, boxSize);
            }
            // joueur sur cible, vers cible
            else if (board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                targetPlayerToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            }
            board->incrementStepCount();
        }
    }else {
        // déplacement impossible
        std::cout << "You shall not pass" << std::endl;
    }
}
