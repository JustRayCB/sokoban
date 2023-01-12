#ifndef _BOARD_HPP
#define _BOARD_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <tuple>

#include "gameObject.hpp"

class Board{
    std::vector<std::vector<GameObject>> gameBoard;
    int posPlayerLine, posPlayerCol;
    std::vector<std::tuple<Point, bool, bool>> targetPos;
    std::vector<Point> tpPos;
    int totalTargets = 0;
    int stepCount = 0;
    int bestScore = 0;
    int limit = 0;
    int boxStuck = 0;

    void copyFromOther(const Board &other){
        posPlayerLine = other.posPlayerLine;
        posPlayerCol = other.posPlayerCol;
        gameBoard = other.gameBoard;
        totalTargets = other.totalTargets;
        targetPos = other.targetPos;
        tpPos = other.tpPos;
        stepCount = other.stepCount;
        bestScore = other.bestScore;
        boxStuck = other.boxStuck;
        limit = other.limit;
    }

public:
    Board(const int nbLine, const int nbCol);
    Board()=default;
    Board(const Board &other);
    Board &operator=(const Board& other);

    /*
     * @brief: Function used to find a path to a certain position in the
     * board to tp the player
     * @param pos: is the current position in the vector (using backtracking)
     * @param target: is the position we should arrived in the end
     * @param visited: is the simulation vector to check if a cell has been
     * visited
     * @param limit: the limit of steps we have to respect
     * @return the number of steps in the path or -1 if there is no possible
     * path (0 if we arrived to the destination)
     */
    int findPath(Point pos, Point target, std::vector<std::vector<bool>>&visited, int limit);
    /*
     * @brief: Function that check if the move for the backtracking is correct
     * @param x, y: coordinate of the pos in the simulation board
     * @param visited: simulation board
     * @return true if ok, else otherwise
     */
    bool isValid(int x, int y, std::vector<std::vector<bool>>&visited);


    GameObject &getElem(const int line, const int col); //return the element of the board [line][col]
                                                        //
    std::vector<std::vector<GameObject>> &getBoard();
    int getPosX() const; //return the x coordinate of the player in the board
    int getPosY() const; //return the y coordinate of the player in the board
    int getTargetsCount() const; //return the number of target filled with a box
    int getTotalTargets(); //return the number total of target
    int getStepCount();
    int getBestScore();
    int getNbLine(); //return the number of line in the game board
    int getNbCol(); //return the number of col in the game board
    int getLimit();

    void setEmpty(const int line, const int col); //Set the cell[line][col] as empty
    void setTp(const int line, const int col); //Set the cell[line][col] as a tp
    void setTarget(const int line, const int col); //Set the cell[line][col] as a target
    void setObject(const int &line, const int &col, GameObject &object); 
    void setPosPlayer(const int &line, const int &col); //modify the position of the player
    void setOnTarget(const Point& position, bool isBox); //Edit the if there is a player or a box on a target
    void removeFromTarget(const Point& position, bool isBox); //Edit the flag to say the target is free
    void setBestScore(const int &score);
    void setLimit(const int &limit);


    void resize(const int &nbLine, const int &nbCol);//resize the 2D vector

    /*
     * @brief: Function that put the right element in the right place of the
     * game board
     * @param line, col: coordinate of the element in the vector
     * @param symbol: representation of the element in the file
     * @param symbol: size of the most common box in the board
     */
    void configBoard(const int &line, const int &col, const char &symbol, const int size);

    void movePlayerInVector(const int newX, const int newY);
    void movBoxInVector(const int newX, const int newY, const int oldX, const int oldY);

    bool isWall(const int line, const int col);
    bool isEmpty(const int line, const int col);
    bool isBox(const int line, const int col);
    bool isTarget(const int line, const int col);
    bool isTp(const int line, const int col);
    bool isInBoard(const int line, const int col);
    bool isWall(Point &position); //overloading
    bool isEmpty(Point &position);
    bool isBox(Point &position);
    bool isTarget(Point &position);
    bool isTp(Point &position);
    bool isGameOver();
    /*
     * @brief: Function that check if the number of steps the user has done
     * has reached the limit
     */
    bool isLimitReached();
    bool hasWon() const;//check if all the target are filled with a box
    /*
     * @brief: Function that check if the element on position in the vector
     * is the position of a target
     */
    bool isOnTarget(const Point &position);
    /*
     * @brief: Function that check if the element on position in the vector
     * is the position of a target
     */
    bool isOnTp(const Point &position);
    bool areBoxStuck(); //check if all the box are stuck in the board
    bool isBoxStuck(int &xVector, int &yVector); //check if the box of position xVector, yVector is stuck

    void incrementTotalTargets();
    void incrementStepCount(int x);

    Point searchMatchTp(const Point &currentTp); // search the other
                                                 //tp if there is one different of the current one

};

void loadBoard(Board &board, std::string file); //function that load a game board using a file


#endif


