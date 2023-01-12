#ifndef _GRID_HPP
#define _GRID_HPP

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>

#include "rectangle.hpp"

/*
* These clases come from the cursus INFOF202 "Langages de programmation 2" of the Université Libre de Bruxelles.
*/

class Cell {
    Rectangle r;
    int current = 0; //current state of the Cell
 public:
    Cell(Point center, int w, int h);
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    int getCurrent();
    void setCurrent(int newCurrent);
};

class Canvas {
    int nbLine = 10;
    int nbCol = 10;
    std::vector<std::vector<Cell>> cells;
 public:
    Canvas(int nbCol=10, int nbLine=10);
    void draw();
    void mouseMove(Point mouseLoc);
    void mouseClick(Point mouseLoc);
    void setNumberOfLines(int lineNumber);
    void setNumberOfColumns(int colNumber);
    int getNumberOfLines();
    int getNumberOfColumns();
    std::vector<std::vector<Cell>> getCells();
    void setCells(std::vector<std::vector<Cell>> newCells);

};

#endif
