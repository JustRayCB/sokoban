#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>
#include <tuple>


#include "board.hpp"
#include "gameObject.hpp"


using namespace std;


Board::Board(const int nbLine, const int nbCol):
    gameBoard(nbLine, std::vector<GameObject>(nbCol)){
}

bool Board::isValid(int x, int y, std::vector<std::vector<bool>>&visited) {
    return isInBoard(x, y) and
        not visited.at(x).at(y) and (isEmpty(x, y) or isTarget(x, y));
}

int Board::findPath(Point pos, Point target, std::vector<std::vector<bool>> &visited, int limit) {
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    
    if (pos.x == target.x and pos.y == target.y) { //we reached the desired position
        return 0;
    }
    if (limit == 0) {
        return -1;
    }
    if (visited.at(pos.x).at(pos.y)) {
        return -1; //the position is already visited
    }

    visited.at(pos.x).at(pos.y) = true;

    int steps = -1;

    for (int i=0; i< 4; i++) {
        int newX = pos.x + dx[i];
        int newY = pos.y + dy[i];
        if (isValid(newX, newY, visited)) {
            int s = findPath(Point{newX, newY}, target, visited, limit-1);
            if (s != -1) steps = s;
        }
    }
    if (steps != -1) return steps + 1; 
    return -1;
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
void Board::incrementStepCount(int x) {stepCount+=x;}
int Board::getBestScore() {return bestScore;}
int Board::getNbCol(){return gameBoard.at(0).size();}
int Board::getNbLine(){return gameBoard.size();}
int Board::getLimit(){return limit;}

void Board::setObject(const int &line, const int &col, GameObject &object){
    getElem(line, col) = object;
}


void Board::setEmpty(const int line, const int col){
    GameObject *willBeEmpty = &getElem(line, col);
    willBeEmpty->setName("empty");
    willBeEmpty->setColor(FL_GRAY);
    willBeEmpty->setFrameColor(FL_GRAY);
}

void Board::setTp(const int line, const int col){
    //std::cout << "Set tp " << std::endl;
    GameObject *willBeTp = &getElem(line, col);
    willBeTp->setName("tp");
    willBeTp->setColor(fl_rgb_color(0, 255, 255));
    willBeTp->setFrameColor(FL_BLACK);
}

void Board::setTarget(const int line, const int col){
    GameObject *willBeTarget = &getElem(line, col);
    willBeTarget->setName("target");
    willBeTarget->setColor(FL_MAGENTA);
    willBeTarget->setFrameColor(FL_BLACK);
    willBeTarget->setSize(willBeTarget->getSize()/2);
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
        setObject(line, col, player); setPosPlayer(line, col);
    }else if (symbol == ' ') {
        GameObject empty{{xGridFltk, yGridFltk}, size, FL_GRAY, FL_GRAY, "empty"};
        setObject(line, col, empty);
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
    }else if (symbol == '/'){
        GameObject tp{{xGridFltk, yGridFltk}, size, FL_BLACK, FL_CYAN, "tp"};
        setObject(line, col, tp);
        tpPos.push_back({line, col});
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
bool Board::isTp(const int line, const int col){ return getElem(line, col).isTp();}
bool Board::isWall(Point &position){ return isWall(position.x, position.y);}
bool Board::isEmpty(Point &position){ return isEmpty(position.x, position.y);}
bool Board::isBox(Point &position){ return isBox(position.x, position.y);}
bool Board::isTarget(Point &position){ return isTarget(position.x, position.y);}
bool Board::isTp(Point &position){ return isTp(position.x, position.y);}


bool Board::isInBoard(const int line, const int col){ 
    return (line < static_cast<int>(gameBoard.size()) and 0 <= line) and 
        (col < static_cast<int>(gameBoard[0].size()) and 0 <= col);
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

bool Board::isOnTp(const Point &position) {
    for (auto &pos : tpPos) {
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
        //std::cout << "All box are on a target" << std::endl;
        return true;
    }
    else if (isLimitReached()){
        //std::cout << "The limit is reached\n";
        return true;
    }
    else if (areBoxStuck()) {
        //std::cout << "The box are stuck, you cannot win the game anymore\n";
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
                //To get all the info from the first line of the file
                std::getline(myFile, lineS);
                stringstream temp(lineS);
                string tempLine, tempCol, tempBestScore, tempLimit;
                getline(temp, tempLine, ' '); getline(temp, tempCol, ' ');
                getline(temp, tempBestScore, ' '); getline(temp, tempLimit, ' ');
                int nbLine = std::stoi(tempLine); int nbCol = std::stoi(tempCol);
                int bestScore = std::stoi(tempBestScore);
                int limit = std::stoi(tempLimit);
                board.setBestScore(bestScore);
                board.setLimit(limit);
                int lineSize = min(600/nbLine, 75);
                int colSize = min(600/nbCol, 75);
                boxSize = min(lineSize, colSize); 
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
    bool upOk = false, downOk = false, leftOk = false, rightOk = false;    
    GameObject *up = nullptr, *down = nullptr, *right = nullptr, *left = nullptr;
    //check if there is up, right, left, down neighbors
    if (isInBoard(xVector-1, yVector)) { upOk = true; up = &getElem(xVector-1, yVector);}
    if (isInBoard(xVector+1, yVector)) { downOk = true;  down = &getElem(xVector+1, yVector); }
    if (isInBoard(xVector, yVector+1)) { rightOk = true; right = &getElem(xVector, yVector+1); }
    if (isInBoard(xVector, yVector-1)) { leftOk = true; left = &getElem(xVector, yVector-1); }
    //check if the box is in a box corner or wall (or both)
    if ((upOk and (up->isWall() or up->isBox()))
            and (rightOk and (right->isWall() or right->isBox()))) { return true; }    
    else if ((upOk and (up->isWall() or up->isBox()))
            and (leftOk and (left->isWall() or left->isBox()))) { return true; }    
    else if ((downOk and (down->isWall() or down->isBox()))
            and (rightOk and (right->isWall() or right->isBox()))) { return true; }    
    else if ((downOk and (down->isWall() or down->isBox()))
            and (leftOk and (left->isWall() or left->isBox()))) { return true; }    

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

    if (totalBox == boxStuck) return true; //if all box are stuck you cannot win the game

    return false;
}



Point Board::searchMatchTp(const Point &currentTp){
    int i = 0, j = 0;
    for (auto &line : gameBoard) {
        j = 0;
        for (auto &elem : line) {
            if (elem.isTp()){
                if (currentTp.x != i or currentTp.y != j) {
                    return {i, j};
                }
            }
            j++;
        }
        i++;
    }
    return {-1, -1};

}
