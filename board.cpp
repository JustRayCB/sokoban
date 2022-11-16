#include <fstream>
#include <vector>
#include <variant>
#include <iostream>
#include <string>


#include "board.hpp"
#include "gameObject.hpp"
#include "player.hpp"
#include "rectangle.hpp"
#include "wall.hpp"

void Board::configBoard(int &line, int &col, char &symbol){
    //Start board at 50,50
    int yGrid = 50*(line+1);
    int xGrid = 50*(col+1);
    if (symbol == '@') {
        //Player
        std::cout << "Pos player at start : " << line << "," << col << std::endl;
        Player myPlayer{{xGrid, yGrid}};
        setPlayer(line, col, myPlayer);
    }
    else if (symbol == ' ') {
        setEmpty(line, col);
    }
    else if (symbol == '#') {
        //Wall
        Wall myWall{{xGrid, yGrid}};
        setWall(line, col, myWall);
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

void Board::movePlayerInBoard(int newX, int newY){
    gameBoard[newX][newY] = gameBoard[posPlayerLine][posPlayerCol];
    setEmpty(posPlayerLine, posPlayerCol);
    posPlayerCol = newY; posPlayerLine = newX;
    
}
void loadBoard(Board &board, std::string file){
    std::ifstream myFile (file);
    int idx = 0;
    std::string lineS;
    int line = 0, col = 0;
    if (myFile.is_open()) {
        while (myFile) {
            if (!idx) {
                //To set the size of the game board
                std::getline( myFile, lineS, ' ');
                int line = std::stoi(lineS);
                lineS = myFile.get();
                int col = std::stoi(lineS);
                board.resize(line, col);
                lineS = myFile.get();    
                //std::cout << line << "real : " << board.getBoard().size() << std::endl;
                //std::cout << col << "real : " << board.getBoard()[0].size() << std::endl;

            }
            std::getline(myFile, lineS);
            for (char &letter :  lineS) {
                board.configBoard(line, col, letter);
                col++;
            }
            col=0;
            line++;
            idx++;
        }
    }
}


void DisplayBoard::draw(){
    //int rows = 0, col = 0;
    for (auto &line : board->getBoard()) {
        for (auto &row : line) {
            //if (row.getName() == "player") {
                //std::cout << "Player pos in game: ";
                //row.getPlayer()->getRectangle().getCenter().printPoint();
                //std::cout << "Player pos in vector :" << rows << "," << col << std::endl;
            //}else if (row.getName()=="wall") {
                //std::cout << "Wall pos in game: ";
                //row.getWall().getPos().printPoint();
                //std::cout << "Wall pos in vector :" << rows << "," << col << std::endl;
                ////row.getWall().

            //}
        row.draw();
        //col++;
        }
        //rows++;
    }
}
void Controll::movePlayer(int keyCode){
    int newX = board->getPosX(), newY = board->getPosY();
    std::cout << "Pos player before when moving: " << newX << "," << newY << std::endl;
    Player *tmp = board->getElem(newX, newY).getPlayer();
    Point PlayerPos = tmp->getPosFltk();
    if (keyCode == FL_Right or keyCode == 'd') {
        std::cout << "Move to the  right" << std::endl;
        //board->getElem(board->getPosX(), board->getPosY()).getPlayer().setPos(x+50, y);
        newY++;
        tmp->setPos(PlayerPos.x + 50, PlayerPos.y);
    }else if (keyCode == FL_Left or keyCode == 'q') {
        newY--;
        std::cout << "Move to the  left" << std::endl;
        tmp->setPos(PlayerPos.x - 50, PlayerPos.y);
    }else if (keyCode == FL_Up or keyCode == 'z') {
        newX--;
        std::cout << "Move up" << std::endl;
        tmp->setPos(PlayerPos.x, PlayerPos.y - 50);
    }else if (keyCode == FL_Down or keyCode == 's') {
        newX++;
        std::cout << "Move down" << std::endl;
        tmp->setPos(PlayerPos.x, PlayerPos.y + 50);
    }
    std::cout << "Pos player after when moving: " << newX << "," << newY << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    tmp->getRectangle().setCenter(tmp->getPosFltk());
    board->movePlayerInBoard(newX, newY);
    
}


void Controll::move(int keyCode){
    int xPlayerVector = board->getPosX(), yPlayerVector = board->getPosY();
    if (keyCode == FL_Right or keyCode == 'd') {
        if (board->isInBoard(xPlayerVector, yPlayerVector+1) and not board->isWall(xPlayerVector, yPlayerVector+1)) {
            this->movePlayer(keyCode);
        }else {
        std::cout << "You shall not pass" << std::endl;
        }

    }else if (keyCode == FL_Left or keyCode == 'q') {
        if (board->isInBoard(xPlayerVector, yPlayerVector-1) and not board->isWall(xPlayerVector, yPlayerVector-1)) {
            this->movePlayer(keyCode);
        }else {
        std::cout << "You shall not pass" << std::endl;
        }

    }else if (keyCode == FL_Up or keyCode == 'z') {
        if (board->isInBoard(xPlayerVector-1, yPlayerVector) and not board->isWall(xPlayerVector-1, yPlayerVector)) {
            this->movePlayer(keyCode);
        }else {
        std::cout << "You shall not pass" << std::endl;
        }


    }else if (keyCode == FL_Down or keyCode == 's') {
        if (board->isInBoard(xPlayerVector+1, yPlayerVector) and not board->isWall(xPlayerVector+1, yPlayerVector)) {
            this->movePlayer(keyCode);
        }else {
        std::cout << "You shall not pass" << std::endl;
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
