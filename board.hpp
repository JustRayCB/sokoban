#ifndef _BOARD_HPP
#define _BOARD_HPP

#include <iostream>
#include <memory>
#include <string>
#include <memory.h>
#include <vector>

#include "gameObject.hpp"
#include "player.hpp"
#include "wall.hpp"

class Board{
    std::vector<std::vector<GameObject>> gameBoard;
    int posPlayerLine, posPlayerCol;
public:
    Board(int nbLine, int nbCol): gameBoard(nbLine, std::vector<GameObject>(nbCol)){}
    Board()=default;
    Board(const Board &other): gameBoard(other.gameBoard), posPlayerLine(other.posPlayerLine), posPlayerCol(other.posPlayerCol){}

    GameObject &getElem(int line, int col) { return gameBoard[line][col];}
    void setPlayer(int &line, int &col, Player &myPlayer){ getElem(line, col).push(myPlayer); posPlayerLine = line, posPlayerCol = col;}
    void setWall(int &line, int &col, Wall &myWall){ getElem(line, col).push(myWall);}
    void setEmpty(int line, int col){ getElem(line, col).push();} //Set the cell as empty
                                                                    
    void configBoard(int &line, int &col, char &symbol, int size);
    
    int getPosX(){ return posPlayerLine;}
    int getPosY(){ return posPlayerCol;}

    void movePlayerInBoard(int newX, int newY);

    void resize(int &nbLine, int &nbCol);

    bool isWall(int line, int col){ return getElem(line, col).getName() == "wall";}
    bool isBox(int line, int col){ return getElem(line, col).getName() == "box";}
    bool isInBoard(int line, int col){ return line<static_cast<int>(gameBoard.size()) and col < static_cast<int>(gameBoard[0].size()-1);}

    std::vector<std::vector<GameObject>> &getBoard() {return gameBoard;}

    Board &operator=(const Board& other);
    void draw();

    

};

class DisplayBoard{
    Board *board = nullptr;
public:
    DisplayBoard(Board &board): board(&board){}
    DisplayBoard()=default;
    void setBoard(Board *myBoard){ board = myBoard;}
    void draw();
};


class Controll{
    Board *board = nullptr;

public:
    void setBoard(Board *myBoard){ board = myBoard;}
    void movePlayer(int keyCode);
    void move(int keyCode);
    void moveBox(int keyCode);

};

void loadBoard(Board &board, std::string file);

#endif


