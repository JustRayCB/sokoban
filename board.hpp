#ifndef _BOARD_HPP
#define _BOARD_HPP

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
    //void setBox(int &line, int &col, Box &myBox){ getElem(line, col).push(myBox);}
    void setEmpty(int &line, int &col){ getElem(line, col).push();} //Set the cell as empty
                                                                    
    void configBoard(int &line, int &col, char &symbol);
    
    std::string getPlayer(){ return std::string(std::to_string(posPlayerLine) + ',' + std::to_string(posPlayerCol));}

    void resize(int &nbLine, int &nbCol);

    std::vector<std::vector<GameObject>> &getBoard() {return gameBoard;}

    Board &operator=(const Board& other);
    void draw();

    

};

class DisplayBoard{
    //std::shared_ptr<Board> board;
    Board *board = nullptr;
public:
    //DisplayBoard(std::shared_ptr<Board> board): board(board){}
    DisplayBoard(Board &board): board(&board){}
    DisplayBoard()=default;
    //void setBoard(std::shared_ptr<Board> &myBoard){ board = myBoard;}
    void setBoard(Board *myBoard){ board = myBoard;}
    void draw();
};


void loadBoard(Board &board, std::string file);

#endif


