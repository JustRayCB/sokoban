#include <FL/Enumerations.H>
#include <iostream>
#include <unistd.h>

#include "controller.hpp"
#include "board.hpp"
#include "gameObject.hpp"
#include "rectangle.hpp"



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
    setDeltas(keyCode, newX, newY, deltaX, deltaY, boxSize, move); //delta sert plus a rien je crois

    board->movePlayerInVector(newX, newY);
    tmp = &board->getElem(newX, newY);
    tmp->setMove(move);
    tmp->addAnimation();

}

void Controll::clickMovePlayer(int x, int y) {
    board->setObject(x, y, board->getElem(board->getPosX(), board->getPosY()));


    if (board->isOnTarget(Point{board->getPosX(), board->getPosY()})) {
        board->removeFromTarget(Point{board->getPosX(), board->getPosY()}, false);
        board->setTarget(board->getPosX(), board->getPosY());
    } else {
        board->setEmpty(board->getPosX(), board->getPosY());
    }
    if (board->isTarget(x,y)) {
        board->setOnTarget(Point{x,y}, false);
    }

    board->setPosPlayer(x, y);

    GameObject *tmp = &board->getElem(x, y);
    const int boxSize = tmp->getSize();
    int newX = 200 + (x*boxSize);
    int newY = 200 + (y*boxSize);
    tmp->setPosFltk(newY, newX);
}

void Controll::tpPlayer(int x, int y){
    //int oldX = board->getPosX(), oldY = board->getPosY();
    //std::cout << "Old x : " << oldX << "\n Old y : " << oldY << std::endl;
    //std::cout << "new x : " << x << "\n new y : " << y << std::endl;


    board->movePlayerInVector(x, y);
    GameObject *tmp = &board->getElem(x, y);
    //std::cout << "Old xFLTK : " << tmp->getPosFltk().x << "\n Old yFLTK : " << tmp->getPosFltk().y << std::endl;
    const int boxSize = tmp->getSize();
    int newX = 200 + (x*boxSize);
    int newY = 200 + (y*boxSize);
    tmp->setPosFltk(newY, newX);
    //std::cout << "new xFLTK : " << tmp->getPosFltk().x << "\n new yFLTK : " << tmp->getPosFltk().y << std::endl;
    
}


void Controll::moveBox(int keyCode, int boxPosX, int boxPosY){
    const int oldX = boxPosX, oldY = boxPosY;
    GameObject *tmp = &board->getElem(boxPosX, boxPosY);
    //const Point boxPosFltk = tmp->getPosFltk();
    const int boxSize = tmp->getSize();
    int deltaX = 0, deltaY = 0; std::string move = "";
    std::cout << "before : " << boxPosX << " , " << boxPosY << std::endl;
    setDeltas(keyCode, boxPosX, boxPosY, deltaX, deltaY, boxSize, move);

    std::cout << "here : " << boxPosX << " , " << boxPosY << std::endl;
    //tmp->setPosFltk(boxPosFltk.x+deltaX, boxPosFltk.y+deltaY);
    board->movBoxInVector(boxPosX, boxPosY, oldX, oldY);
    tmp = &board->getElem(boxPosX, boxPosY);
    tmp->setMove(move);
    tmp->addAnimation();

}


void Controll::emptyPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la case vide
    GameObject empty{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize, FL_GRAY, FL_GRAY, "empty"};
    board->setObject(position.x, position.y, empty);
}
void Controll::emptyPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
}

void Controll::emptyPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_MAGENTA);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la case vide
    GameObject empty{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize, FL_GRAY, FL_GRAY, "empty"};
    board->setObject(position.x, position.y, empty);
}

void Controll::emptyPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_YELLOW);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, false);
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la case vide
    GameObject empty{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize, FL_GRAY, FL_GRAY, "empty"};
    board->setObject(position.x, position.y, empty);
}

void Controll::emptyPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    emptyPlayerToTp({position.x +deltaX, position.y+deltaY}, position, keyCode);
}

void Controll::emptyPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la case vide
    GameObject empty{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize, FL_GRAY, FL_GRAY, "empty"};
    board->setObject(position.x, position.y, empty);
}

void Controll::targetPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}

void Controll::tpPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    emptyPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    board->setTp(position.x, position.y);
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

void Controll::tpPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    tpPlayerToEmpty(position, keyCode);
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

void Controll::tpPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    board->setTp(position.x+deltaX, position.y+deltaY);
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

void Controll::emptyPlayerToEmpty(const Point &position, int keyCode, int boxSize){
    this->movePlayer(keyCode);
    // on redessine la case vide
    GameObject empty{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize, FL_GRAY, FL_GRAY, "empty"};
    board->setObject(position.x, position.y, empty);
}
void Controll::emptyPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->movePlayer(keyCode);
    // on redessine la case vide
    GameObject empty{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize, FL_GRAY, FL_GRAY, "empty"};
    board->setObject(position.x, position.y, empty);
}
void Controll::tpPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->movePlayer(keyCode);
    board->setTp(position.x, position.y);
}

void Controll::tpPlayerToEmpty(const Point &position, int keyCode){
    this->movePlayer(keyCode);
    board->setTp(position.x, position.y);
}

void Controll::emptyPlayerToTp(const Point &newPosition, const Point &oldPosition, int keyCode){
    Point matchTp = board->searchMathTp(newPosition);
    if (matchTp.x != -1) {
        this->tpPlayer(matchTp.x, matchTp.y);
        board->setEmpty(oldPosition.x, oldPosition.y);
        board->setTp(newPosition.x, newPosition.y);
    }else {
        movePlayer(keyCode);
    }
}

void Controll::targetPlayerToEmpty(const Point &position, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    this->movePlayer(keyCode);
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}
void Controll::targetPlayerToTp(const Point &newPosition, const Point &oldPosition, int keyCode){
    board->removeFromTarget(Point{oldPosition.x, oldPosition.y}, false);
    Point matchTp = board->searchMathTp(newPosition);
    if (matchTp.x != -1) {
        this->tpPlayer(matchTp.x, matchTp.y);
        board->setTp(newPosition.x, newPosition.y);
    }else {
        movePlayer(keyCode);
    }
    board->setTarget(oldPosition.x, oldPosition.y);
}
void Controll::targetPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->movePlayer(keyCode);
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}
    
void Controll::tpPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    emptyPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    board->setTp(position.x, position.y);
}

void Controll::tpPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    emptyPlayerEmptyBoxToTarget(position, deltaX, deltaY, keyCode, boxSize);
    board->setTp(position.x, position.y);
}

void Controll::emptyPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    emptyPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
}

void Controll::targetPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    targetPlayerToTp({position.x+deltaX, position.y+deltaY}, position, keyCode);
    std::cout << position.x+2*deltaX << " ," << position.y+2*deltaY << std::endl;
}
void Controll::emptyPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+2*deltaX, position.y+2*deltaY).setColor(FL_MAGENTA);
    emptyPlayerToTp({position.x+deltaX, position.y+deltaY}, position, keyCode);
}
void Controll::targetPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    targetPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
}

void Controll::tpPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){ 
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+2*deltaX, position.y+2*deltaY).setColor(FL_MAGENTA);
    board->setTp(position.x+deltaX, position.y+deltaY);
}
void Controll::tpPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){ 
    emptyPlayerTargetBoxToTp(position, deltaX, deltaY, keyCode, boxSize);
    board->setTp(position.x, position.y);
}
void Controll::targetPlayerTpBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){ 
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    targetPlayerToTp({position.x+deltaX, position.y+deltaY}, position, keyCode);
}
void Controll::targetPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){ 
    targetPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
}
void Controll::targetPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){ 
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_MAGENTA);
    targetPlayerTpBoxToEmpty(position, deltaX, deltaY, keyCode);
}
void Controll::tpPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){ 
    tpPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+2*deltaX, position.y+2*deltaY).setColor(FL_MAGENTA);
    board->setTp(position.x, position.y);

}


void Controll::manageFromEmptyPlayer(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point destinationPosition = {position.x+deltaX, position.y+deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        emptyPlayerToTarget(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        emptyPlayerToTp(destinationPosition, position, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        emptyPlayerToEmpty(position, keyCode, boxSize);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTargetPlayer(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point destinationPosition = {position.x+deltaX, position.y+deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        targetPlayerToTarget(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        targetPlayerToTp(destinationPosition, position, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        targetPlayerToEmpty(position, keyCode, boxSize);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTpPlayer(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+deltaX, position.y+deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        tpPlayerToTarget(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        tpPlayerToEmpty(position, keyCode);
    } else {
        perror("Mouvement non pris en charge");
    }
}


void Controll::manageMovePlayer(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    // joueur sur vide, vers vide
    //std::cout << "Yo" << std::endl;
    if (not board->isOnTarget(position) and not board->isOnTp(position)) {
        // joueur est sur une case vide
        manageFromEmptyPlayer(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isOnTarget(position)) {
        // joueur est sur une cible
        manageFromTargetPlayer(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isOnTp(position)) {
        // joueur est sur un tp
        manageFromTpPlayer(position, deltaX, deltaY, keyCode);
    }   
}

void Controll::manageFromEmptyPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        emptyPlayerEmptyBoxToTarget(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        emptyPlayerEmptyBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        emptyPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromEmptyPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        emptyPlayerTargetBoxToTarget(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        emptyPlayerTargetBoxToTp(position, deltaX, deltaY, keyCode, boxSize);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        emptyPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromEmptyPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        emptyPlayerTpBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        emptyPlayerEmptyBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        emptyPlayerTpBoxToEmpty(position, deltaX, deltaY, keyCode);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTargetPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        targetPlayerEmptyBoxToTarget(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        targetPlayerEmptyBoxToTp(position, deltaX, deltaY, keyCode, boxSize);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        targetPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTargetPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        targetPlayerTargetBoxToTarget(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        targetPlayerTargetBoxToTp(position, deltaX, deltaY, keyCode, boxSize);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        targetPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTargetPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        targetPlayerTpBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        targetPlayerTpBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        targetPlayerTpBoxToEmpty(position, deltaX, deltaY, keyCode);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTpPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        tpPlayerEmptyBoxToTarget(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        tpPlayerEmptyBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        tpPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTpPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        tpPlayerTargetBoxToTarget(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        tpPlayerTargetBoxToTp(position, deltaX, deltaY, keyCode, boxSize);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        tpPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode, boxSize);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTpPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        tpPlayerTpBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        tpPlayerTpBoxToEmpty(position, deltaX, deltaY, keyCode);
    } else {
        perror("Mouvement non pris en charge");
    }
}



void Controll::manageMovePlayerAndBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize) {
    Point boxPosition = {position.x+deltaX, position.y+deltaY};
    if (not board->isOnTarget(position) and not board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur vide box sur vide
            manageFromEmptyPlayerEmptyBox(position, deltaX, deltaY, keyCode, boxSize);
    } else if (not board->isOnTarget(position) and not board->isOnTp(position)
        and board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur vide box sur cible
            manageFromEmptyPlayerTargetBox(position, deltaX, deltaY, keyCode, boxSize);
    } else if (not board->isOnTarget(position) and not board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and board->isOnTp(boxPosition)) {
            // Joueur sur vide box sur tp
            manageFromEmptyPlayerTpBox(position, deltaX, deltaY, keyCode);
    } else if (board->isOnTarget(position) and not board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur cible box sur vide
            manageFromTargetPlayerEmptyBox(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isOnTarget(position) and not board->isOnTp(position)
        and board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur cible box sur cible
            manageFromTargetPlayerTargetBox(position, deltaX, deltaY, keyCode, boxSize);
    } else if (board->isOnTarget(position) and not board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and board->isOnTp(boxPosition)) {
            // Joueur sur cible box sur tp
            manageFromTargetPlayerTpBox(position, deltaX, deltaY, keyCode);
    } else if (not board->isOnTarget(position) and board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur tp box sur vide
            manageFromTpPlayerEmptyBox(position, deltaX, deltaY, keyCode, boxSize);
    } else if (not board->isOnTarget(position) and board->isOnTp(position)
        and board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur tp box sur cible
            manageFromTpPlayerTargetBox(position, deltaX, deltaY, keyCode, boxSize);
    } else if (not board->isOnTarget(position) and board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and board->isOnTp(boxPosition)) {
            // Joueur sur tp box sur tp
            manageFromTpPlayerTpBox(position, deltaX, deltaY, keyCode);
    }
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
                    or board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)
                or board->isOnTp({xIdx+2*deltaX, yIdx+2*deltaY}));
        if (isBoxMovable) {
            manageMovePlayerAndBox({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            board->incrementStepCount(1);
        }
        else if (not board->isBox(xIdx+deltaX, yIdx+deltaY)) {
            manageMovePlayer({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            board->incrementStepCount(1);
        }
    }else {
        // déplacement impossible
        std::cout << "You shall not pass" << std::endl;
    }
}
