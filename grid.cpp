#include "grid.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>


Cell::Cell(Point center, int w, int h) : r(center, w, h, FL_BLACK, FL_WHITE) {}

void Cell::draw() {
    if (current == 0) {
        r.setFillColor(FL_WHITE);
    } else if (current == 1) {
        r.setFillColor(FL_BLUE);
    } else if (current == 2) {
        r.setFillColor(FL_YELLOW);
    } else if (current == 3) {
        r.setFillColor(FL_GREEN);
    } else if (current == 4) {
        r.setFillColor(FL_MAGENTA);
    } else if (current == 5) {
        r.setFillColor(FL_CYAN);
    }
    r.draw();
}

void Cell::mouseMove(Point mouseLoc) {
    if (r.contains(mouseLoc)) {
        r.setFrameColor(FL_RED);
    } else {
        r.setFrameColor(FL_BLACK);
    }
}

void Cell::mouseClick(Point mouseLoc) { 
    if (r.contains(mouseLoc)) {
        current++;
        if (current == 6) {
            current = 0;
        }
    }
}

int Cell::getCurrent() {
    return current;
}

void Cell::setCurrent(int newCurrent) {
    current = newCurrent;
}

Canvas::Canvas(int nbColone, int nbLigne) {
    std::cout << "Entering Canva constructor with dimensions: " << nbLigne << " " << nbColone << std::endl;
    int size = std::min(500/nbColone, 500/nbLigne);
    for(int i=0; i < nbLigne; i++){
        std::vector<Cell> innerVec;
        for(int j=0; j < nbColone; j++){
            innerVec.push_back(Cell{Point{(size/2)+j*size, (200+size/2)+i*size}, size, size});
        }
        cells.push_back(innerVec);
    }
}

void Canvas::draw() {
    for (auto &c:cells) {
        for (auto &cc:c) {
            cc.draw();
        }
    }
}
void Canvas::mouseMove(Point mouseLoc) {
  for (auto &c:cells) {
    for (auto &cc:c) {
        cc.mouseMove(mouseLoc);
    }
  }
}
void Canvas::mouseClick(Point mouseLoc) {
  for (auto &c:cells) {
    for (auto &cc:c) {
        cc.mouseClick(mouseLoc);
    }
  }
}
void Canvas::setNumberOfColumns(int colNumber){
    nbCol = colNumber;
}
void Canvas::setNumberOfLines(int lineNumber){
    nbLine = lineNumber;
}
int Canvas::getNumberOfColumns(){
    return nbCol;
}
int Canvas::getNumberOfLines(){
    return nbLine;
}

std::vector<std::vector<Cell>> Canvas::getCells() {
    return cells;
}

void Canvas::setCells(std::vector<std::vector<Cell>> newCells) {
    cells = newCells;
}
