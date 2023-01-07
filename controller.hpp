#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP

#include "board.hpp"
#include <string>

class Controll{
    Board *board = nullptr;

public:
    void setBoard(Board *myBoard);//{ board = myBoard;}
                                  
    void movePlayer(int keyCode);
    void tpPlayer(int x, int y);
    void moveBox(int keyCode, int boxPosX, int boxPosY);
    void move(int keyCode);

    void setDeltas(int &keycode, int &xVector, int &yVector, int &deltaX, 
        int &deltaY, const int &boxSize, std::string &move);
    // void boxTargetToEmpty(GameObject &box);

    void clickMovePlayer(int x, int y);

    void manageMovePlayer(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageMovePlayerAndBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    
    void manageFromEmptyPlayer(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageFromTargetPlayer(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageFromTpPlayer(const Point &position, int deltaX, int deltaY, int keyCode);

    void manageFromEmptyPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageFromEmptyPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageFromEmptyPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode);
    void manageFromTargetPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageFromTargetPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageFromTargetPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode);
    void manageFromTpPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageFromTpPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void manageFromTpPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode);


    //Possible moves with a box
    void emptyPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    void emptyPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    void emptyPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void tpPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void tpPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    void targetPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void tpPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    void targetPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    
    //Possible moves without a box
    void emptyPlayerToEmpty(const Point &position, int keyCode, int boxSize);
    void emptyPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerToTp(const Point &position, const Point &oldPosition, int keyCode);
    void tpPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    void tpPlayerToEmpty(const Point &position, int keyCode);
    void targetPlayerToEmpty(const Point &position, int keyCode, int boxSize);
    void targetPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerToTp(const Point &newPosition, const Point &oldPosition, int  keyCode);
    

    void tpPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void tpPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void emptyPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    void emptyPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    void targetPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void tpPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    void tpPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerTpBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    void targetPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    void targetPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    void tpPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
};



#endif
