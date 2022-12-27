#include "grid.hpp"
#include <cstring>
#include <iostream>
#include <algorithm>


Cell::Cell(Point center, int w, int h) : r(center, w, h, FL_BLACK, FL_WHITE) {}

void Cell::draw() {
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
        if (current == 0) {
            r.setFillColor(FL_BLUE);
            current++;
        } else if (current == 1) {
            r.setFillColor(FL_YELLOW);
            current++;
        } else if (current == 2) {
            r.setFillColor(FL_GREEN);
            current++;
        } else if (current == 3) {
            r.setFillColor(FL_MAGENTA);
            current++;
        } else if (current == 4) {
            r.setFillColor(FL_WHITE);
            current -= 4;
        }
    }
}

int Cell::getCurrent() {
    return current;
}

Canvas::Canvas(int nbColone, int nbLigne) {
    int size = std::min(500/nbColone, 500/nbLigne);
    for(int i=0; i < nbLigne; i++){
        for(int j=0; j < nbColone; j++){
            cells.push_back(Cell{Point{(size/2)+i*size, (200+size/2)+j*size}, size, size});
        }
    }
}

void Canvas::draw() {
    for (auto &c:cells) {
        c.draw();
    }
}
void Canvas::mouseMove(Point mouseLoc) {
  for (auto &c:cells) c.mouseMove(mouseLoc);
}
void Canvas::mouseClick(Point mouseLoc) {
  for (auto &c:cells) c.mouseClick(mouseLoc);
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

std::vector<Cell> Canvas::getCells() {
    return cells;
}