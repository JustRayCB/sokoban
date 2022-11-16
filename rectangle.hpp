#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <chrono>
#include <iostream>
#include <math.h>
#include <random>
#include <string>
#include <time.h>
#include <vector>

struct Point {
    int x, y;
    void printPoint();
};

class Rectangle {
    //Variables
    Point center;
    int w = 20, h=20;
    Fl_Color fillColor, frameColor;

public:
    //Methods
    Rectangle()=default;
    Rectangle(Point center, int w=20, int h=20, Fl_Color frameColor = FL_WHITE,
              Fl_Color fillColor = FL_GREEN);

    Rectangle &operator=(const Rectangle &other){
        center = other.center;
        w = other.w; h = other.h;
        fillColor = other.fillColor; frameColor = other.frameColor;
        return *this;
    }
    void draw();

    void setFillColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFrameColor);

    bool contains(Point p);

    Point getCenter() const { return center; }
    void setCenter(int &x, int &y){ center.x = x; center.y = y;}
    void setCenter(Point newCenter){ center = newCenter;}
};

#endif
