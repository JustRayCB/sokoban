#include <FL/Enumerations.H>
#include <iostream>
#include <unistd.h>
#include <FL/fl_ask.H>

#include "controller.hpp"
#include "board.hpp"
#include "gameObject.hpp"
#include "rectangle.hpp"


void Controll::mouseMove(Point mouseLoc) {
    for (auto &c:board->getBoard()) {
        for (auto &cc:c) {
            cc.mouseMove(mouseLoc);
        }
    }
}

void Controll::setBoard(Board *myBoard){
    board = myBoard;
}

void Controll::setDeltas(int &keyCode, int &xVector, int &yVector, std::string &move){
    if (keyCode == FL_Up or keyCode == 'z') {xVector--; move = "up";}
    else if (keyCode == FL_Left or keyCode == 'q') {yVector--; move = "left";}
    else if (keyCode == FL_Down or keyCode == 's') {xVector++; move = "down";}
    else if (keyCode == FL_Right or keyCode == 'd') {yVector++; move = "right";}

}

void Controll::movePlayer(int keyCode){
    int newX = board->getPosX(), newY = board->getPosY();
    GameObject *tmp = &board->getElem(newX, newY);
    std::string move = "";
    setDeltas(keyCode, newX, newY, move);
    board->movePlayerInVector(newX, newY);
    tmp = &board->getElem(newX, newY); //get the player cause he moved in the vector
    tmp->setMove(move);
    tmp->addAnimation();

}

void Controll::moveBox(int keyCode, int boxPosX, int boxPosY){
    int oldX = boxPosX, oldY = boxPosY;
    GameObject *tmp = &board->getElem(boxPosX, boxPosY);
    std::string move = "";
    setDeltas(keyCode, boxPosX, boxPosY, move);
    board->movBoxInVector(boxPosX, boxPosY, oldX, oldY);
    tmp = &board->getElem(boxPosX, boxPosY); //get the box caus it moved in the vector
    tmp->setMove(move);
    tmp->addAnimation();

}

void Controll::clickMovePlayer(int x, int y) {
    Point oldPos = {board->getPosX(), board->getPosY()};
    tpPlayer(x, y);

    if (board->isOnTarget(oldPos)) {
        board->removeFromTarget(oldPos, false);
        board->setTarget(oldPos.x, oldPos.y);
    }
    if (board->isTarget(x,y)) {
        board->setOnTarget(Point{x,y}, false);
    }
}

void Controll::tpPlayer(int x, int y){
    board->movePlayerInVector(x, y);
    GameObject *tmp = &board->getElem(x, y);
    const int boxSize = tmp->getSize();
    int newX = 200 + (x*boxSize);
    int newY = 200 + (y*boxSize);
    tmp->setPosFltk(newY, newX);
}


void Controll::emptyPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    emptyPlayerToEmpty(position, keyCode);
}
void Controll::emptyPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
}

void Controll::emptyPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_MAGENTA);
    emptyPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode);
}

void Controll::emptyPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_YELLOW);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, false);
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la case vide
    board->setEmpty(position.x, position.y);
}

void Controll::emptyPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    emptyPlayerToTp({position.x +deltaX, position.y+deltaY}, position, keyCode);
}

void Controll::emptyPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la case vide
    board->setEmpty(position.x, position.y);
}

void Controll::targetPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    board->removeFromTarget(Point{position.x, position.y}, false);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    board->setTarget(position.x, position.y);
}

void Controll::tpPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    emptyPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode);
    board->setTp(position.x, position.y);
}

void Controll::targetPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_MAGENTA);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    board->setTarget(position.x, position.y);
}

void Controll::tpPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    tpPlayerToEmpty(position, keyCode);
}

void Controll::targetPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_YELLOW);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    board->setTarget(position.x, position.y);
}

void Controll::tpPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    board->setTp(position.x+deltaX, position.y+deltaY);
}

void Controll::targetPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->removeFromTarget(Point{position.x+deltaX, position.y+deltaY}, true);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la cible
    board->setTarget(position.x, position.y);
}

void Controll::emptyPlayerToEmpty(const Point &position, int keyCode){
    this->movePlayer(keyCode);
    // on redessine la case vide
    board->setEmpty(position.x, position.y);
}
void Controll::emptyPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->movePlayer(keyCode);
    // on redessine la case vide
    board->setEmpty(position.x, position.y);
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
    Point matchTp = board->searchMatchTp(newPosition);
    if (matchTp.x != -1) {
        tpPlayer(matchTp.x, matchTp.y);
        board->setEmpty(oldPosition.x, oldPosition.y);
        board->setTp(newPosition.x, newPosition.y);
    }else {
        movePlayer(keyCode);
    }
}

void Controll::targetPlayerToEmpty(const Point &position, int keyCode){
    board->removeFromTarget(Point{position.x, position.y}, false);
    this->movePlayer(keyCode);
    board->setTarget(position.x, position.y);
}
void Controll::targetPlayerToTp(const Point &newPosition, const Point &oldPosition, int keyCode){
    board->removeFromTarget(Point{oldPosition.x, oldPosition.y}, false);
    Point matchTp = board->searchMatchTp(newPosition);
    if (matchTp.x != -1) {
        this->tpPlayer(matchTp.x, matchTp.y);
        board->setTp(newPosition.x, newPosition.y);
    }else {
        movePlayer(keyCode);
    }
    board->setTarget(oldPosition.x, oldPosition.y);
}
void Controll::targetPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    board->removeFromTarget(Point{position.x, position.y}, false);
    board->setOnTarget(Point{position.x+deltaX, position.y+deltaY}, false);
    this->movePlayer(keyCode);
    board->setTarget(position.x, position.y);
}
    
void Controll::tpPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    emptyPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode);
    board->setTp(position.x, position.y);
}

void Controll::tpPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    emptyPlayerEmptyBoxToTarget(position, deltaX, deltaY, keyCode);
    board->setTp(position.x, position.y);
}

void Controll::emptyPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){
    emptyPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode);
}

void Controll::targetPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode){
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    targetPlayerToTp({position.x+deltaX, position.y+deltaY}, position, keyCode);
}
void Controll::emptyPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+2*deltaX, position.y+2*deltaY).setColor(FL_MAGENTA);
    emptyPlayerToTp({position.x+deltaX, position.y+deltaY}, position, keyCode);
}
void Controll::targetPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){
    targetPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode);
}

void Controll::tpPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){ 
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+2*deltaX, position.y+2*deltaY).setColor(FL_MAGENTA);
    board->setTp(position.x+deltaX, position.y+deltaY);
}
void Controll::tpPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){ 
    emptyPlayerTargetBoxToTp(position, deltaX, deltaY, keyCode);
    board->setTp(position.x, position.y);
}
void Controll::targetPlayerTpBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){ 
    moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    targetPlayerToTp({position.x+deltaX, position.y+deltaY}, position, keyCode);
}
void Controll::targetPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode){
    targetPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode);
}
void Controll::targetPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){ 
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+deltaX, position.y+deltaY).setColor(FL_MAGENTA);
    targetPlayerTpBoxToEmpty(position, deltaX, deltaY, keyCode);
}
void Controll::tpPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode){ 
    tpPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode);
    board->setOnTarget(Point{position.x+2*deltaX, position.y+2*deltaY}, true);
    board->getElem(position.x+2*deltaX, position.y+2*deltaY).setColor(FL_MAGENTA);
    board->setTp(position.x, position.y);

}


void Controll::manageFromEmptyPlayer(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+deltaX, position.y+deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        emptyPlayerToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        emptyPlayerToTp(destinationPosition, position, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        emptyPlayerToEmpty(position, keyCode);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTargetPlayer(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+deltaX, position.y+deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        targetPlayerToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        targetPlayerToTp(destinationPosition, position, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        targetPlayerToEmpty(position, keyCode);
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


void Controll::manageMovePlayer(const Point &position, int deltaX, int deltaY, int keyCode) {
    // joueur sur vide, vers vide
    //std::cout << "Yo" << std::endl;
    if (not board->isOnTarget(position) and not board->isOnTp(position)) {
        // joueur est sur une case vide
        manageFromEmptyPlayer(position, deltaX, deltaY, keyCode);
    } else if (board->isOnTarget(position)) {
        // joueur est sur une cible
        manageFromTargetPlayer(position, deltaX, deltaY, keyCode);
    } else if (board->isOnTp(position)) {
        // joueur est sur un tp
        manageFromTpPlayer(position, deltaX, deltaY, keyCode);
    }   
}

void Controll::manageFromEmptyPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        emptyPlayerEmptyBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        emptyPlayerEmptyBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        emptyPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromEmptyPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        emptyPlayerTargetBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        emptyPlayerTargetBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        emptyPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode);
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

void Controll::manageFromTargetPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        targetPlayerEmptyBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        targetPlayerEmptyBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        targetPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTargetPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        targetPlayerTargetBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        targetPlayerTargetBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        targetPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode);
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

void Controll::manageFromTpPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        tpPlayerEmptyBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        tpPlayerEmptyBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        tpPlayerEmptyBoxToEmpty(position, deltaX, deltaY, keyCode);
    } else {
        perror("Mouvement non pris en charge");
    }
}

void Controll::manageFromTpPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point destinationPosition = {position.x+2*deltaX, position.y+2*deltaY};
    if (board->isTarget(destinationPosition)) {
        // vers target
        tpPlayerTargetBoxToTarget(position, deltaX, deltaY, keyCode);
    } else if (board->isTp(destinationPosition)) {
        // vers tp
        tpPlayerTargetBoxToTp(position, deltaX, deltaY, keyCode);
    } else if (not board->isTarget(destinationPosition)
            and not board->isTp(destinationPosition)) {
        // vers vide
        tpPlayerTargetBoxToEmpty(position, deltaX, deltaY, keyCode);
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



void Controll::manageMovePlayerAndBox(const Point &position, int deltaX, int deltaY, int keyCode) {
    Point boxPosition = {position.x+deltaX, position.y+deltaY};
    if (not board->isOnTarget(position) and not board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur vide box sur vide
            manageFromEmptyPlayerEmptyBox(position, deltaX, deltaY, keyCode);
    } else if (not board->isOnTarget(position) and not board->isOnTp(position)
        and board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur vide box sur cible
            manageFromEmptyPlayerTargetBox(position, deltaX, deltaY, keyCode);
    } else if (not board->isOnTarget(position) and not board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and board->isOnTp(boxPosition)) {
            // Joueur sur vide box sur tp
            manageFromEmptyPlayerTpBox(position, deltaX, deltaY, keyCode);
    } else if (board->isOnTarget(position) and not board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur cible box sur vide
            manageFromTargetPlayerEmptyBox(position, deltaX, deltaY, keyCode);
    } else if (board->isOnTarget(position) and not board->isOnTp(position)
        and board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur cible box sur cible
            manageFromTargetPlayerTargetBox(position, deltaX, deltaY, keyCode);
    } else if (board->isOnTarget(position) and not board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and board->isOnTp(boxPosition)) {
            // Joueur sur cible box sur tp
            manageFromTargetPlayerTpBox(position, deltaX, deltaY, keyCode);
    } else if (not board->isOnTarget(position) and board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur tp box sur vide
            manageFromTpPlayerEmptyBox(position, deltaX, deltaY, keyCode);
    } else if (not board->isOnTarget(position) and board->isOnTp(position)
        and board->isOnTarget(boxPosition) and not board->isOnTp(boxPosition)) {
            // Joueur sur tp box sur cible
            manageFromTpPlayerTargetBox(position, deltaX, deltaY, keyCode);
    } else if (not board->isOnTarget(position) and board->isOnTp(position)
        and not board->isOnTarget(boxPosition) and board->isOnTp(boxPosition)) {
            // Joueur sur tp box sur tp
            manageFromTpPlayerTpBox(position, deltaX, deltaY, keyCode);
    }
}


void Controll::move(int keyCode){
    /*
     * z (up)-> deltaX = -1, deltaY = 0
     * q (left)-> deltaX = 0, deltaY = -1 
     * s (down)-> deltaX = +1, deltaY = 0
     * d (right)-> deltaX = 0, deltaY = +1
     */

    int deltaX = 0, deltaY = 0;

    //set the delta in order to get the move coordinate for the new position of the player
    if (keyCode == FL_Up or keyCode == 'z') {deltaX--;}
    else if (keyCode == FL_Left or keyCode == 'q') {deltaY--;}
    else if (keyCode == FL_Down or keyCode == 's') {deltaX++;}
    else if (keyCode == FL_Right or keyCode == 'd') {deltaY++;}
    else {return;}

    //int xIdx = board->getPosX(), yIdx = board->getPosY();
    Point playerPosition = {board->getPosX(), board->getPosY()};
    Point futurePlayerPosition = {playerPosition.x+deltaX, playerPosition.y+deltaY}; //aka boxPosition
    Point futureBoxPosition = {futurePlayerPosition.x+deltaX, futurePlayerPosition.y + deltaY};

    bool isPlayerMovable = board->isInBoard(futurePlayerPosition.x, futurePlayerPosition.y) 
                        and not board->isWall(futurePlayerPosition.x, futurePlayerPosition.y);
    if (isPlayerMovable){
        bool isBoxMovable = board->isBox(futurePlayerPosition) and board->isInBoard(futureBoxPosition.x, futureBoxPosition.y)
            and not (board->isWall(futureBoxPosition) or board->isBox(futureBoxPosition));
                //and (board->isEmpty(futureBoxPosition) 
                    //or board->isTarget(futureBoxPosition)
                //or board->isOnTp({futureBoxPosition}));
        if (isBoxMovable) {
            manageMovePlayerAndBox(playerPosition, deltaX, deltaY, keyCode);
            board->incrementStepCount(1);
        }
        else if (not board->isBox(futurePlayerPosition)) {
            manageMovePlayer(playerPosition, deltaX, deltaY, keyCode);
            board->incrementStepCount(1);
        }
    }else {
        // déplacement impossible
        std::cout << "You shall not pass" << std::endl;
    }
}

Point Controll::mouseClick(Point mouseLoc) {
  for (auto &c:board->getBoard()) {
    for (auto &cc:c) {
        Point p = cc.mouseClick(mouseLoc);
        if (p.x != - 1) {
            return p;
        }
    }
  } 
  return {-1,-1};
}


void Controll::moveWithMouse(int eventX, int eventY){

    Point test = mouseClick({eventX, eventY});
    std::vector<std::vector<bool>> visited(board->getBoard().size(), std::vector<bool>(board->getBoard()[0].size(), false));
    int steps = board->findPath(Point{board->getPosX(), board->getPosY()}, test, visited, board->getLimit()-board->getStepCount());
    if (steps != -1) {
        std::cout << "FOUND A PATH OF " << steps << "STEPS" << std::endl;
        board->incrementStepCount(steps);
        clickMovePlayer(test.x, test.y);
    } else {
        fl_alert("No path found in limit of steps");
    }
    }
