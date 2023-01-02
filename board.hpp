#ifndef _BOARD_HPP
#define _BOARD_HPP

#include <iostream>
#include <memory>
#include <string>
#include <memory.h>
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
    }

public:
    Board(const int nbLine, const int nbCol);
    Board()=default;
    Board(const Board &other);
    Board &operator=(const Board& other);

    void mouseMove(Point mouseLoc);
    Point mouseClick(Point mouseLoc);
    bool findPath(Point pos, Point target, std::vector<std::vector<bool>>&visited);
    bool isValid(int x, int y, std::vector<std::vector<bool>>&visited);
    int getBoxSize();

    GameObject &getElem(const int line, const int col);
    std::vector<std::vector<GameObject>> &getBoard();
    int getPosX() const;
    int getPosY() const;
    int getTargetsCount() const;
    int getTotalTargets();
    int getStepCount();
    int getBestScore();
    int getNbLine();
    int getNbCol();
    int getLimit();

    void setEmpty(const int line, const int col); //Set the cell as empty
    void setTp(const int line, const int col); //Set the cell as empty
    void setTarget(const int line, const int col); //Set the cell as empty
    void setObject(const int &line, const int &col, GameObject &object);
    void setPosPlayer(const int &line, const int &col);
    void setOnTarget(const Point& position, bool isBox);
    void setOnTp(const Point& position, bool isBox);
    void removeFromTarget(const Point& position, bool isBox);
    void removeFromTp(const Point& position, bool isBox);
    void setBestScore(const int &score);
    void setLimit(const int &limit);


    void resize(const int &nbLine, const int &nbCol);
                                                                    
    void configBoard(const int &line, const int &col, const char &symbol, const int size);

    void movePlayerInVector(const int newX, const int newY);
    void movBoxInVector(const int newX, const int newY, const int oldX, const int oldY);

    bool isWall(const int line, const int col);
    bool isEmpty(const int line, const int col);
    bool isBox(const int line, const int col);
    bool isTarget(const int line, const int col);
    bool isTp(const int line, const int col);
    bool isInBoard(const int line, const int col);
    bool isGameOver();
    bool isLimitReached();
    bool hasWon() const;
    bool wasOnTarget(const Point &position, bool isBox);
    bool wasOnTp(const Point &position, bool isBox);
    bool isOnTarget(const Point &position);
    bool isOnTp(const Point &position);
    bool areBoxStuck();
    bool isBoxStuck(int &xVector, int &yVector);

    void draw();

    void incrementTotalTargets();
    void incrementStepCount();

    Point searchMathTp(const Point &currentTp);
    void replaceTp();

};

void loadBoard(Board &board, std::string file);


#endif


