#include <iostream>

#include "board.hpp"
#include "display.hpp"

DisplayBoard::DisplayBoard(Board &board): board(&board){
}


void DisplayBoard::setBoard(Board *myBoard){
    board = myBoard;
}


class Text {
  std::string s;
  Point center;
  int fontSize;
  Fl_Color color;

 public:
  // Constructor
  Text(std::string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK):
    s{s}, center{center}, fontSize{fontSize}, color{color} {}

  // Draw
  void draw();

  // Setters and getters
  std::string getString() {
    return s;
  }
  void setString(const std::string &newString) {
    s = newString;
  }
  int getFontSize() {
    return fontSize;
  }
  void setFontSize(int newFontSize) {
    fontSize = newFontSize;
  }
  Point getCenter() {
    return center;
  }
  void setCenter(Point newCenter) {
    center = newCenter;
  }
};

void Text::draw(){
    fl_color(color);
    fl_font(FL_HELVETICA, fontSize);
    int width, height;
    fl_measure(s.c_str(), width, height, false);
    fl_draw(s.c_str(), center.x-width/2, center.y-fl_descent()+height/2);
}


void DisplayBoard::draw(){
    for (auto &line : board->getBoard()) {
        for (auto &row : line) {
            if (row.getName() != "empty") {
                row.draw(); 
            }
        }
    }
    int c = board->getTargetsCount();
    int stepCount = board->getStepCount();

    Text text1{std::to_string(c), {830, 200}, 20, FL_BLACK};
    Text text2{std::to_string(stepCount), {830, 400}, 20, FL_BLACK};
    Text text3{std::to_string(board->getBestScore()), {830, 600}, 20, FL_BLACK};
    Text text4{std::to_string(board->getLimit()), {830, 800}, 20, FL_BLACK};

    text2.setString("steps: "+std::to_string(stepCount));
    text3.setString("Best score: " + std::to_string(board->getBestScore()));
    text4.setString("Limit: " + std::to_string(board->getLimit()));
    if (c == board->getTotalTargets()){
        text1.setString("You won !!");
    } 
    else if (board->getStepCount()==board->getLimit() and not board->isGameOver()) {
        text1.setString("You Loose !!");
    
    }
    else {
        text1.setString("targets: "+std::to_string(c)+"/"+std::to_string(board->getTotalTargets()));
    }
    
    text1.draw();
    text2.draw();
    text3.draw();
    text4.draw();
}


