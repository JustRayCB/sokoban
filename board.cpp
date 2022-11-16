#include <fstream>
#include <vector>
#include <variant>
#include <iostream>
#include <string>


#include "board.hpp"
#include "gameObject.hpp"
#include "player.hpp"
#include "wall.hpp"

void Board::configBoard(int &line, int &col, char &symbol){
    //Start board at 50,50
    int xGrid = 50*(line+1);
    int yGrid = 50*(col+1);
    if (symbol == '@') {
        //std::cout << symbol << ", ";
        //Player
        Player myPlayer{{xGrid, yGrid}};
        setPlayer(line, col, myPlayer);
        //std::cout << getElem(line, col).getName() << std::endl;
        //std::cout <<  getElem(line, col).getPlayer().getPos().x << ", " << getElem(line, col).getPlayer().getPos().y << std::endl;
    }
    else if (symbol == ' ') {
        //std::cout << symbol << ", ";
        setEmpty(line, col);
    }
    else if (symbol == '#') {
        //Wall
        //std::cout << symbol << ", ";
        Wall myWall{{xGrid, yGrid}};
        setWall(line, col, myWall);
        //std::cout << getElem(line, col).getName() << std::endl;
        //std::cout <<  getElem(line, col).getWall().getPos().x << ", " << getElem(line, col).getWall().getPos().y << std::endl;

    }
}

Board& Board::operator=(const Board &other){
    posPlayerLine = other.posPlayerLine;
    posPlayerCol = other.posPlayerCol;
    gameBoard = other.gameBoard;
    return *this;
}

void Board::resize(int &nbLine, int &nbCol){
    gameBoard.resize(nbLine, std::vector<GameObject>(nbCol));
}

void loadBoard(Board &board, std::string file){
    std::ifstream myFile (file);
    int idx = 0;
    std::string lineS;
    int line = 0, col = 0;
    if (myFile.is_open()) {
        //std::cout << "[ ";
        while (myFile) {
            if (!idx) {
                //To set the size of the game board
                std::getline( myFile, lineS, ' ');
                int line = std::stoi(lineS);
                lineS = myFile.get();
                int col = std::stoi(lineS);
                //std::cout << "line : " << line  << ", col : " << col << std::endl;
                board.resize(line, col);
                lineS = myFile.get();    

            }
            std::getline(myFile, lineS);
            //std::cout << tmp << std::endl;
            //std::cout << "[ ";
            for (char &letter :  lineS) {
                board.configBoard(line, col, letter);
                col++;
            }
            
            //std::cout << "], " << std::endl;
            col=0;
            line++;
            idx++;
        }
        //std::cout << "] ";
    }
}


void DisplayBoard::draw(){
    for (auto &line : board->getBoard()) {
        for (auto &row : line) {
            row.draw();
        }
    }
}

//void Board::draw(){
    //for (auto &line : gameBoard) {
        //for (auto &row : line) {
            //if (row.getName() == "wall") {
            //}
            //row.draw();
        //}
    //}
//}
//int main(int argc,char* argv[]){
    //std::cout << "nb : " << argc << std::endl;
    //std::cout << argv[0] << std::endl;
    //std::cout << argv[1] << std::endl;

    //Board board;
    //loadBoard(board, argv[1]);
    //std::cout << "here" << std::endl;
    //return 0;
//}
