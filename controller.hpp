#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP

#include "board.hpp"
#include <string>

class Controll{
    Board *board = nullptr;

public:

    void mouseMove(Point mouseLoc);
    Point mouseClick(Point mouseLoc);

    void setBoard(Board *myBoard);

    /*
     * @brief: Function that will make the player make the right move
     * @param keyCode: key that represent the move
     */
    void movePlayer(int keyCode);
    /*
     * @brief: Function that will find a path to the clicked cell
     * to move the player on it
     */
    void moveWithMouse(int eventX, int eventY);
    /*
     * @brief: Function that will make the box make the right move
     * @param keyCode: key that represent the move
     * @param boxPosX: position of the box in the vector coordinate X
     * @param boxPosY: position of the box in the vector coordinate Y
     */
    void moveBox(int keyCode, int boxPosX, int boxPosY);
    /*
     * @brief: Function that will check if the keyCode
     * is ok to make the player move according to all elements around
     * @param keyCode: key pressed by the player
     */
    void move(int keyCode);
    /*
     * @brief: Function that teleport a player from his initial position to a new positon
     * @param x: X coordinate of the new position
     * @param y: Y coordinate of the new position
     */
    void tpPlayer(int x, int y);

    /*
     * @brief: Function that teleport a player from his initial position to a new positon
     * @param keyCode: key pressed by the player
     * @param xVector: X coordinate of the player's position in the vector
     * @param yVector: Y coordinate of the player's position in the vector
     * @param move: move that the player wants to do {up, down, right, left}
     */
    void setDeltas(int &keycode, int &xVector, int &yVector, std::string &move);

    /*
     * @brief: Function that manage to move the player when a case of 
     * the board is clicked
     * @param x: the vector coordinate X position where the player wants to go
     * @param y: the vector coordinate Y position where the player wants to go
     */
    void clickMovePlayer(int x, int y);

    /*
     * @brief: Function that manage the possible moves of a player alone
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     * @param boxSize: size of the box of the corresponding object
     */
    void manageMovePlayer(const Point &position, int deltaX, int deltaY, int keyCode, int boxSize);
    /*
     * @brief: Function that manage the possible moves of a player and a box
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageMovePlayerAndBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on an empty case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromEmptyPlayer(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a target case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromTargetPlayer(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a teleportation case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromTpPlayer(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a empty case that is pushing a box
     * that is on an empty case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromEmptyPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a empty case that is pushing a box
     * that is on an target case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromEmptyPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a empty case that is pushing a box
     * that is on an teleportation case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromEmptyPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a target case that is pushing a box
     * that is on an empty case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromTargetPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a target case that is pushing a box
     * that is on an target case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromTargetPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a target case that is pushing a box
     * that is on an teleportation case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromTargetPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a teleportation case that is pushing a box
     * that is on an empty case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromTpPlayerEmptyBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a teleportation case that is pushing a box
     * that is on an target case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromTpPlayerTargetBox(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that manage the possible moves of a player that is on a teleportation case that is pushing a box
     * that is on an teleportation case
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void manageFromTpPlayerTpBox(const Point &position, int deltaX, int deltaY, int keyCode);


    //Possible moves with a box
    /*
     * @brief: Function that moves a player that is on an empty case pushing a box that is on an empty case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case pushing a box that is on an empty case to a teleportation case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case pushing a box that is on an empty case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case pushing a box that is on a target case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case pushing a box that is on a teleportation case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case pushing a box that is on a target case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case pushing a box that is on a empty case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case pushing a box that is on an empty case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     * @param boxSize: size of the box of the corresponding object
     */
    void tpPlayerEmptyBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case pushing a box that is on an empty case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case pushing a box that is on an empty case to a teleportation case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void tpPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case pushing a box that is on a target case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on teleportation case pushing a box that is on a teleportation case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void tpPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on target case pushing a box that is on a target case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case pushing a box that is on a target case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void tpPlayerTargetBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case pushing a box that is on an empty case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void tpPlayerEmptyBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case pushing a box that is on a target case to a teleportation case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case pushing a box that is on a teleportation case to an empty case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerTpBoxToEmpty(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case pushing a box that is on a teleportation case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case pushing a box that is on an empty case to a teleportation case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerEmptyBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case pushing a box that is on a teleportation case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void tpPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case pushing a box that is on a target case to a teleportation case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void tpPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case pushing a box that is on a teleportation case to a teleportation case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerTpBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case pushing a box that is on a target case to a teleportation case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerTargetBoxToTp(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case pushing a box that is on a teleportation case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerTpBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case pushing a box that is on a target case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void tpPlayerTargetBoxToTarget(const Point &position, int deltaX, int deltaY, int keyCode);




    //Possible moves without a box
    /*
     * @brief: Function that moves a player that is on an empty case to an empty case 
     * @param position: the position of the player in the vector 
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerToEmpty(const Point &position, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void emptyPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on an empty case to a teleportation case 
     * @param position: the new position of the player in the vector 
     * @param oldPosition: the old position of the player in the vector 
     */
    void emptyPlayerToTp(const Point &position, const Point &oldPosition, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void tpPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a teleportation case to an empty case 
     * @param position: the position of the player in the vector 
     * @param keyCode: key pressed by the player
     */
    void tpPlayerToEmpty(const Point &position, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case to an empty case 
     * @param position: the position of the player in the vector 
     * @param keyCode: key pressed by the player
     */
    void targetPlayerToEmpty(const Point &position, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case to a target case 
     * @param position: the position of the player in the vector 
     * @param deltaX: the corresponding delta of the X axe of the move that the player wants to make 
     * @param deltaY: the corresponding delta of the Y axe of the move that the player wants to make
     * @param keyCode: key pressed by the player
     */
    void targetPlayerToTarget(const Point &position, int deltaX, int deltaY, int keyCode);
    /*
     * @brief: Function that moves a player that is on a target case to a teleportation case 
     * @param position: the new position of the player in the vector 
     * @param position: the old position of the player in the vector
     */
    void targetPlayerToTp(const Point &newPosition, const Point &oldPosition, int  keyCode);
    

};



#endif
