#include <algorithm>
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
#include "box.hpp"
#include "target.hpp"

void Board::configBoard(int &line, int &col, char &symbol, int size){
    //Start board at 200,200
    std::cout << "here :" << size << std::endl;
    int yGrid = 200+(line*size);
    int xGrid = 200+(col*size);
    if (symbol == '@') {
        //Player
        std::cout << "Pos player at start : " << line << "," << col << std::endl;
        Player myPlayer{{xGrid, yGrid}, size};
        setPlayer(line, col, myPlayer);
    }
    else if (symbol == ' ') {
        setEmpty(line, col);
    }
    else if (symbol == '#') {
        //Wall
        Wall myWall{{xGrid, yGrid}, size};
        setWall(line, col, myWall);
    }
    else if (symbol == '$') {
        Box myBox{{xGrid, yGrid}, size};
        setBox(line, col, myBox);
    }
    else if (symbol == '.'){
        Target myTarget{{xGrid, yGrid}, size/2};
        setTarget(line, col, myTarget);
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

void Board::movBoxInBoard(int newX, int newY, int oldX, int oldY){
    gameBoard[newX][newY] = gameBoard[oldX][oldY];
}


void loadBoard(Board &board, std::string file){
    std::ifstream myFile (file);
    int idx = 0;
    std::string lineS;
    int line = 0, col = 0, boxSize = 70;
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
                boxSize = std::min(500/line, 500/col);
                //boxSize = std::min(500, 50);
                //std::cout << std::min(500/line, 500/col) << std::endl;

            }
            std::getline(myFile, lineS);
            for (char &letter :  lineS) {
                board.configBoard(line, col, letter, boxSize);
                col++;
            }
            col=0;
            line++;
            idx++;
        }
    }
}



void Controll::moveBox(int keyCode, int boxPosX, int boxPosY){ 
    int oldX = boxPosX, oldY = boxPosY;
    std::cout << "Pos box before when moving: " << boxPosX << "," << boxPosY << std::endl;
    Box *tmp = board->getElem(boxPosX, boxPosY).getBox();
    Point BoxPos = tmp->getPosFltk();
    int boxSize = tmp->getSize();

    if (keyCode == FL_Right or keyCode == 'd') {
        std::cout << "Move to the  right" << std::endl;
        //board->getElem(board->getPosX(), board->getPosY()).getPlayer().setPos(x+50, y);
        boxPosY++;
        tmp->setPos(BoxPos.x + boxSize, BoxPos.y);
    }else if (keyCode == FL_Left or keyCode == 'q') {
        boxPosY--;
        std::cout << "Move to the  left" << std::endl;
        tmp->setPos(BoxPos.x - boxSize, BoxPos.y);
    }else if (keyCode == FL_Up or keyCode == 'z') {
        boxPosX--;
        std::cout << "Move up" << std::endl;
        tmp->setPos(BoxPos.x, BoxPos.y - boxSize);
    }else if (keyCode == FL_Down or keyCode == 's') {
        boxPosX++;
        std::cout << "Move down" << std::endl;
        tmp->setPos(BoxPos.x, BoxPos.y + boxSize);
    }
    std::cout << "Pos box after when moving: " << boxPosX << "," << boxPosY << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    tmp->getRectangle().setCenter(tmp->getPosFltk());
    board->movBoxInBoard(boxPosX, boxPosY, oldX, oldY);

}


void Controll::movePlayer(int keyCode){
    int newX = board->getPosX(), newY = board->getPosY();
    std::cout << "Pos player before when moving: " << newX << "," << newY << std::endl;
    Player *tmp = board->getElem(newX, newY).getPlayer();
    Point PlayerPos = tmp->getPosFltk();
    int boxSize = tmp->getSize();
    if (keyCode == FL_Right or keyCode == 'd') {
        std::cout << "Move to the  right" << std::endl;
        newY++;
        tmp->setPos(PlayerPos.x + boxSize, PlayerPos.y);
    }else if (keyCode == FL_Left or keyCode == 'q') {
        newY--;
        std::cout << "Move to the  left" << std::endl;
        tmp->setPos(PlayerPos.x - boxSize, PlayerPos.y);
    }else if (keyCode == FL_Up or keyCode == 'z') {
        newX--;
        std::cout << "Move up" << std::endl;
        tmp->setPos(PlayerPos.x, PlayerPos.y - boxSize);
    }else if (keyCode == FL_Down or keyCode == 's') {
        newX++;
        std::cout << "Move down" << std::endl;
        tmp->setPos(PlayerPos.x, PlayerPos.y + boxSize);
    }
    std::cout << "Pos player after when moving: " << newX << "," << newY << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    tmp->getRectangle().setCenter(tmp->getPosFltk());
    board->movePlayerInBoard(newX, newY);
    
}


void Controll::move(int keyCode){
    int xPlayerVector = board->getPosX(), yPlayerVector = board->getPosY();
    if (keyCode == FL_Right or keyCode == 'd') {
        if (board->isInBoard(xPlayerVector, yPlayerVector+1) and not board->isWall(xPlayerVector, yPlayerVector+1)){
            if (board->isBox(xPlayerVector, yPlayerVector+1) and board->isInBoard(xPlayerVector, yPlayerVector+2)  and (board->isEmpty(xPlayerVector, yPlayerVector+2) or board->isTarget(xPlayerVector, yPlayerVector+2))) {
                // déplacement vers la droite avec box
                if (board->isTarget(xPlayerVector, yPlayerVector+2)) {
                    // on est sur une cible
                    Box *tmp = board->getElem(xPlayerVector, yPlayerVector+1).getBox();
                    tmp->setBoxColor();
                }
                this->moveBox(keyCode, xPlayerVector, yPlayerVector+1);
                this->movePlayer(keyCode);
            }
            else if (not board->isBox(xPlayerVector, yPlayerVector+1)) {
                // déplacement vers la droite sans box
                this->movePlayer(keyCode);
            }
        }else {
            // déplacement vers la droite impossible
            std::cout << "You shall not pass" << std::endl;
        }

    }else if (keyCode == FL_Left or keyCode == 'q') {
        if (board->isInBoard(xPlayerVector, yPlayerVector-1) and not board->isWall(xPlayerVector, yPlayerVector-1)){
            if (board->isBox(xPlayerVector, yPlayerVector-1) and board->isInBoard(xPlayerVector, yPlayerVector-2)  and (board->isEmpty(xPlayerVector, yPlayerVector-2) or board->isTarget(xPlayerVector, yPlayerVector-2))) {
                // déplacement vers la gauche avec box
                if (board->isTarget(xPlayerVector, yPlayerVector-2)) {
                    // on est sur une cible
                    Box *tmp = board->getElem(xPlayerVector, yPlayerVector-1).getBox();
                    tmp->setBoxColor();
                }
                this->moveBox(keyCode, xPlayerVector, yPlayerVector-1);
                this->movePlayer(keyCode);
            }
            else if (not board->isBox(xPlayerVector, yPlayerVector-1)) {
                // déplacement vers la gauche sans box
                this->movePlayer(keyCode);
            }

        }else {
        std::cout << "You shall not pass" << std::endl;
        }

    }else if (keyCode == FL_Up or keyCode == 'z') {
        if (board->isInBoard(xPlayerVector-1, yPlayerVector) and not board->isWall(xPlayerVector-1, yPlayerVector)){
            if (board->isBox(xPlayerVector-1, yPlayerVector) and board->isInBoard(xPlayerVector-2, yPlayerVector)  and (board->isEmpty(xPlayerVector-2, yPlayerVector) or board->isTarget(xPlayerVector-2, yPlayerVector))) {
                // déplacement vers le haut avec box
                if (board->isTarget(xPlayerVector-2, yPlayerVector)) {
                    // on est sur une cible
                    Box *tmp = board->getElem(xPlayerVector-1, yPlayerVector).getBox();
                    tmp->setBoxColor();
                }
                this->moveBox(keyCode, xPlayerVector-1, yPlayerVector);
                this->movePlayer(keyCode);
            }
            else if (not board->isBox(xPlayerVector-1, yPlayerVector)) {
                // déplacement vers le haut sans box
                this->movePlayer(keyCode);
            }

        }else {
        std::cout << "You shall not pass" << std::endl;
        }


    }else if (keyCode == FL_Down or keyCode == 's') {
        if (board->isInBoard(xPlayerVector+1, yPlayerVector) and not board->isWall(xPlayerVector+1, yPlayerVector)){
            if (board->isBox(xPlayerVector+1, yPlayerVector) and board->isInBoard(xPlayerVector+2, yPlayerVector)  and (board->isEmpty(xPlayerVector+2, yPlayerVector) or board->isTarget(xPlayerVector+2, yPlayerVector))) {
                // déplacement vers le bas avec box
                if (board->isTarget(xPlayerVector+2, yPlayerVector)) {
                    // on est sur une cible
                    Box *tmp = board->getElem(xPlayerVector+1, yPlayerVector).getBox();
                    tmp->setBoxColor();
                }
                this->moveBox(keyCode, xPlayerVector+1, yPlayerVector);
                this->movePlayer(keyCode);
            }
            else if (not board->isBox(xPlayerVector+1, yPlayerVector)) {
                // déplacement vers le bas sans box
                this->movePlayer(keyCode);
            }
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

