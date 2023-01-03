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

void Controll::tpPlayer(int x, int y){
    int oldX = board->getPosX(), oldY = board->getPosY();
    std::cout << "Old x : " << oldX << "\n Old y : " << oldY << std::endl;
    std::cout << "new x : " << x << "\n new y : " << y << std::endl;


    board->movePlayerInVector(x, y);
    GameObject *tmp = &board->getElem(x, y);
    std::cout << "Old xFLTK : " << tmp->getPosFltk().x << "\n Old yFLTK : " << tmp->getPosFltk().y << std::endl;
    const int boxSize = tmp->getSize();
    int newX = 200 + (x*boxSize);
    int newY = 200 + (y*boxSize);
    tmp->setPosFltk(newY, newX);
    std::cout << "new xFLTK : " << tmp->getPosFltk().x << "\n new yFLTK : " << tmp->getPosFltk().y << std::endl;
    
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


void Controll::emptyPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize){
    this->moveBox(keyCode, position.x+deltaX, position.y+deltaY);
    this->movePlayer(keyCode);
    // on redessine la case vide
    GameObject empty{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize, FL_GRAY, FL_GRAY, "empty"};
    board->setObject(position.x, position.y, empty);
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
    board->setEmpty(position.x, position.y);
    board->replaceTp();
}

void Controll::tpPlayerToEmpty(int keyCode){
    this->movePlayer(keyCode);
    board->replaceTp();
}

void Controll::emptyPlayerToTp(const Point &newPosition, const Point &oldPosition){
    Point matchTp = board->searchMathTp(newPosition);
    std::cout << "Current tp : " << newPosition.x << ", " << newPosition.y << std::endl;
    std::cout << "New tp : " << matchTp.x << ", " << matchTp.y << std::endl;
    this->tpPlayer(matchTp.x, matchTp.y);
    board->setEmpty(oldPosition.x, oldPosition.y);
    board->setTp(newPosition.x, newPosition.y);
    //GameObject empty{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize, FL_GRAY, FL_GRAY, "empty"};
    //board->setObject(position.x, position.y, empty);

}

void Controll::targetPlayerToEmpty(const Point &position, int keyCode, int boxSize){
    board->removeFromTarget(Point{position.x, position.y}, false);
    this->movePlayer(keyCode);
    GameObject target{{200+position.y*boxSize, 200+position.x*boxSize}, boxSize/2, FL_BLACK, FL_MAGENTA, "target"};
    board->setObject(position.x, position.y, target);
}
void Controll::targetPlayerToTp(const Point &newPosition, const Point &oldPosition){
    board->removeFromTarget(Point{oldPosition.x, oldPosition.y}, false);
    Point matchTp = board->searchMathTp(newPosition);
    std::cout << "Current tp : " << newPosition.x << ", " << newPosition.y << std::endl;
    std::cout << "New tp : " << matchTp.x << ", " << matchTp.y << std::endl;
    this->tpPlayer(matchTp.x, matchTp.y);
    board->setTarget(oldPosition.x, oldPosition.y);
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
                emptyPlayerEmptyBoxToEmpty({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            }
            // joueur sur vide, box sur vide, vers cible
            else if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                emptyPlayerEmptyBoxToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            // joueur sur vide, box sur cible, vers vide
            } 
            else if (not board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and not board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)) {
                emptyPlayerTargetBoxToEmpty({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            }
            // joueur sur vide, box sur cible, vers cible
            else if (not board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY}) and board->isTarget(xIdx+2*deltaX, yIdx+2*deltaY)){
                emptyPlayerTargetBoxToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
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
            board->incrementStepCount(1);
        }
        else if (not board->isBox(xIdx+deltaX, yIdx+deltaY)) {
            // joueur sur vide, vers vide
            std::cout << "Yo" << std::endl;
            if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY})
                    and not board->isTp(xIdx+deltaX, yIdx+deltaY)
                    and not board->isOnTp({xIdx, yIdx})) {
                emptyPlayerToEmpty({xIdx, yIdx}, keyCode, boxSize);
            std::cout << "MPTY" << std::endl;
            }
            // joueur sur vide, vers cible
            else if (not board->isOnTarget({xIdx, yIdx}) and not board->isOnTp({xIdx, yIdx})
                    and board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                emptyPlayerToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            std::cout << "Target" << std::endl;
            }
            // joueur sur cible, vers vide
            else if (board->isOnTarget({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY})
                    and not board->isTp(xIdx+deltaX, yIdx+deltaY)) {
                targetPlayerToEmpty({xIdx, yIdx}, keyCode, boxSize);
            std::cout << "MTPY 2" << std::endl;
            }
            // joueur sur cible, vers cible
            else if (board->isOnTarget({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
            std::cout << "Target2" << std::endl;
                targetPlayerToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode, boxSize);
            }

            //joueur sur Tp vers cible
            else if (board->isOnTp({xIdx, yIdx}) and board->isOnTarget({xIdx+deltaX, yIdx+deltaY})) {
                std::cout << "Tp vers target" << std::endl;
                //emptyPlayerToTp({xIdx+deltaX, yIdx+deltaY}, {xIdx, yIdx});
                tpPlayerToTarget({xIdx, yIdx}, deltaX, deltaY, keyCode);

            }
            //joueur sur vide, vers tp
            else if (not board->isOnTarget({xIdx, yIdx}) and board->isTp(xIdx+deltaX, yIdx+deltaY)) {
                std::cout << "Teleportation" << std::endl;
                emptyPlayerToTp({xIdx+deltaX, yIdx+deltaY}, {xIdx, yIdx});
            }
            //tp vers vide
            else if (board->isOnTp({xIdx, yIdx}) and not board->isOnTarget({xIdx+deltaX, yIdx+deltaY})
                    and not board->isTp(xIdx+deltaX, yIdx+deltaY)) {
                std::cout << "tp vers vide " << std::endl;
                tpPlayerToEmpty(keyCode);
            }
            //joueur sur cible, vers tp
            else if (board->isOnTarget({xIdx, yIdx}) and board->isTp(xIdx+deltaX, yIdx+deltaY)) {
                std::cout << "cible vers tp" << std::endl;
                targetPlayerToTp({xIdx+deltaX, yIdx+deltaY}, {xIdx, yIdx});
            
            }
            board->incrementStepCount(1);
        }
    }else {
        // déplacement impossible
        std::cout << "You shall not pass" << std::endl;
    }
}
