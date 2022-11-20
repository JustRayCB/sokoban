#ifndef _BOARD_HPP
#define _BOARD_HPP

#include <iostream>
#include <memory>
#include <string>
#include <memory.h>
#include <vector>

#include "gameObject.hpp"

class Board{
    std::vector<std::vector<GameObject>> gameBoard;
    int posPlayerLine, posPlayerCol;

    void copyFromOther(const Board &other){
        posPlayerLine = other.posPlayerLine;
        posPlayerCol = other.posPlayerCol;
        gameBoard = other.gameBoard;
    }

public:
    Board(const int nbLine, const int nbCol);
    Board()=default;
    Board(const Board &other);
    Board &operator=(const Board& other);

    GameObject &getElem(const int line, const int col);
    std::vector<std::vector<GameObject>> &getBoard();
    int getPosX() const;
    int getPosY() const;

    void setEmpty(const int line, const int col); //Set the cell as empty
    void setObject(const int &line, const int &col, GameObject &object);
    void setPosPlayer(const int &line, const int &col);


    void resize(const int &nbLine, const int &nbCol);
                                                                    
    void configBoard(const int &line, const int &col, const char &symbol, const int size);

    void movePlayerInVector(const int newX, const int newY);
    void movBoxInVector(const int newX, const int newY, const int oldX, const int oldY);

    bool isWall(const int line, const int col);
    bool isEmpty(const int line, const int col);
    bool isBox(const int line, const int col);
    bool isTarget(const int line, const int col);
    bool isInBoard(const int line, const int col);
    //bool isInBoard(int line, int col);//{ return line<static_cast<int>(gameBoard.size()) and col < static_cast<int>(gameBoard[0].size()-1);}


    void draw();

    

};

void loadBoard(Board &board, std::string file);

//class DisplayBoard{
    //Board *board = nullptr;
//public:
    //DisplayBoard(Board &board): board(&board){}
    //DisplayBoard()=default;
    //void setBoard(Board *myBoard){ board = myBoard;}
    //void draw();
//};


//class Controll{
    //Board *board = nullptr;

//public:
    //void setBoard(Board *myBoard){ board = myBoard;}
    //void movePlayer(int keyCode);
    //void move(int keyCode);
    //void moveBox(int keyCode, int boxPosX, int boxPosY);

//};


#endif


