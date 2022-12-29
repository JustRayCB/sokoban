#include <FL/Enumerations.H>
#include <algorithm>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <variant>
#include <iostream>
#include <string>
#include <tuple>


#include "board.hpp"
#include "gameObject.hpp"
#include "rectangle.hpp"


using namespace std;


Board::Board(const int nbLine, const int nbCol):
    gameBoard(nbLine, std::vector<GameObject>(nbCol)){
}


Board::Board(const Board &other){
    copyFromOther(other);
}


Board& Board::operator=(const Board &other){
    copyFromOther(other);
    return *this;
}


GameObject& Board::getElem(const int line, const int col){
    return gameBoard.at(line).at(col);
}


int Board::getPosX() const{
    return posPlayerLine;
}


int Board::getPosY() const{
    return posPlayerCol;
}


std::vector<std::vector<GameObject>>& Board::getBoard(){
    return gameBoard;
}

int Board::getTotalTargets() {return totalTargets;}
void Board::incrementTotalTargets() {totalTargets++;}
int Board::getStepCount() {return stepCount;}
void Board::incrementStepCount() {stepCount++;}
int Board::getBestScore() {return bestScore;}
int Board::getNbCol(){return gameBoard.at(0).size();}
int Board::getNbLine(){return gameBoard.size();}
int Board::getLimit(){return limit;}

void Board::setObject(const int &line, const int &col, GameObject &object){
    getElem(line, col) = object;
}


void Board::setEmpty(const int line, const int col){
    getElem(line, col).setName("empty");
}


void Board::setPosPlayer(const int &x, const int &y){
    posPlayerLine = x;
    posPlayerCol = y;
}

void Board::setBestScore(const int &score){
    bestScore = score;
}

void Board::setLimit(const int &newLimit){ limit = newLimit; }

void Board::resize(const int &nbLine, const int &nbCol){
    gameBoard.resize(nbLine, std::vector<GameObject>(nbCol));
}


void Board::configBoard(const int &line, const int &col, const char &symbol, const int size){
    //we start to display the board at 200,200
    
    int xGridFltk = 200+(col*size); 
    int yGridFltk = 200+(line*size); 

    if (symbol == '@') {
        //Player
        GameObject player{{xGridFltk, yGridFltk}, size, FL_BLACK, FL_GREEN, "player"};
        setObject(line, col, player);
        setPosPlayer(line, col);
    }else if (symbol == ' ') {
        //Nothing
        setEmpty(line, col);
    }else if (symbol == '#') {
        //Wall
        GameObject wall{{xGridFltk, yGridFltk}, size, FL_BLACK, FL_BLUE, "wall"};
        setObject(line, col, wall);
    }else if (symbol == '.') {
        //Target
        GameObject target{{xGridFltk, yGridFltk}, size/2, FL_BLACK, FL_MAGENTA, "target"};
        setObject(line, col, target);
        targetPos.push_back(make_tuple(Point{line, col}, false, false));
        incrementTotalTargets();
    }else if (symbol == '$') {
        //Box
        GameObject box{{xGridFltk, yGridFltk}, size, FL_BLACK, FL_YELLOW, "box"};
        setObject(line, col, box);
    }
}


void Board::movePlayerInVector(const int newX, const int newY){
    setObject(newX, newY, getElem(getPosX(), getPosY()));
    setEmpty(getPosX(), getPosY());
    setPosPlayer(newX, newY);
}

void Board::movBoxInVector(const int newX, const int newY, const int oldX, const int oldY){
    setObject(newX, newY, getElem(oldX, oldY));
}

bool Board::isWall(const int line, const int col){ return getElem(line, col).isWall();}
bool Board::isEmpty(const int line, const int col){ return getElem(line, col).isEmpty();}
bool Board::isBox(const int line, const int col){ return getElem(line, col).isBox();}
bool Board::isTarget(const int line, const int col){ return getElem(line, col).isTarget();}
bool Board::isInBoard(const int line, const int col){ 
    bool res =  (line < static_cast<int>(gameBoard.size()) and 0 <= line) and 
        (col < static_cast<int>(gameBoard[0].size()) and 0 <= col);
    return res;
}
bool Board::isLimitReached(){ return limit == stepCount; }

void Board::setOnTarget(const Point &position, bool isBox) {
    for (auto& [pos, boolPlayer, boolBox] : targetPos) {
        if (pos == position) {
            if (isBox) {boolBox = true;}
            else {boolPlayer = true;}
            break;
        }
    }
}

void Board::removeFromTarget(const Point &position, bool isBox){
    for (auto& [pos, boolPlayer, boolBox] : targetPos) {
        if (pos == position){
            if (isBox){boolBox = false;}
            else {boolPlayer = false;}
            break;
        }
    }
}

bool Board::isOnTarget(const Point &position) {
    for (auto& [pos, boolPlayer, boolBox] : targetPos) {
        if (position == pos) {
            return true;
        }
    }
    return false;
}

int Board::getTargetsCount() const{
    int count = 0;
    for (auto& [pos, boolPlayer, boolBox] : targetPos) {
        if (boolBox) {count++;}
    }
    return count;
}

bool Board::hasWon() const{
    return static_cast<size_t>(getTargetsCount()) == targetPos.size();
}

bool Board::isGameOver() {
    if (hasWon()){
        std::cout << "All box are on a target" << std::endl;
        return true;
    }
    else if (isLimitReached()){
        std::cout << "The limit is reached\n";
        return true;
    }
    else if (areBoxStuck()) {
        std::cout << "The box are stuck, you cannot win the game anymore\n";
        return true;
    }
    return false;
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
                std::getline(myFile, lineS);
                stringstream temp(lineS);
                string tempLine, tempCol, tempBestScore, tempLimit;
                getline(temp, tempLine, ' ');
                getline(temp, tempCol, ' ');
                getline(temp, tempBestScore, ' ');
                getline(temp, tempLimit, ' ');
                int nbLine = std::stoi(tempLine);
                int nbCol = std::stoi(tempCol);
                int bestScore = std::stoi(tempBestScore);
                int limit = std::stoi(tempLimit); //if error set limit = 0
                board.setBestScore(bestScore);
                board.setLimit(limit);
                boxSize = 600/nbLine;
                board.resize(nbLine, nbCol);

            }
            std::getline(myFile, lineS);
             for (char &letter :  lineS) {
                 board.configBoard(line, col, letter, boxSize);
                 col++;
             }
            col=0;
            line++;idx++;
        }
    }
}

bool Board::isBoxStuck(int &xVector, int &yVector){
    std::vector<std::tuple<int, int>> coord = {{xVector+1, yVector}, {xVector-1, yVector},
                                                {xVector, yVector+1},{xVector, yVector-1}};
    bool upOk = false, downOk = false, leftOk = false, rightOk = false;    
    GameObject *up = nullptr, *down = nullptr, *right = nullptr, *left = nullptr;
    if (isInBoard(xVector, yVector-1)) { upOk = true; up = &getElem(xVector, yVector-1);}
    if (isInBoard(xVector, yVector+1)) { downOk = true;  down = &getElem(xVector, yVector+1); }
    if (isInBoard(xVector+1, yVector)) { rightOk = true; right = &getElem(xVector+1, yVector); }
    if (isInBoard(xVector-1, yVector)) { leftOk = true; left = &getElem(xVector-1, yVector); }
    bool onTarget = isOnTarget({xVector, yVector});
    std::cout << "Box is on target : " << onTarget << std::endl;
    if ((upOk and up->isWall())
            and (rightOk and right->isWall()) and not onTarget) { return true; }    
    else if ((upOk and up->isWall())
            and (leftOk and left->isWall()) and not onTarget) { return true; }    
    else if ((downOk and down->isWall())
            and (rightOk and right->isWall()) and not onTarget) { return true; }    
    else if ((downOk and down->isWall())
            and (leftOk and left->isWall()) and not onTarget) { return true; }    

    return false;
}

bool Board::areBoxStuck(){

    int boxStuck = 0;
    int totalBox = 0;

    for (int line = 0; static_cast<std::size_t>(line) < gameBoard.size(); line++) {
        for (int col = 0; static_cast<std::size_t>(col) < gameBoard.at(line).size(); col++) {
            if (isBox(line, col)){
                totalBox++;
                if (isBoxStuck(line, col)) { boxStuck++; }
            }
        }
    }

    if (totalBox-boxStuck < totalTargets) {
        return true;
    }

    return false;
}

