#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <string>
#include <vector>

/*
* These clases come from the cursus INFOF202 "Langages de programmation 2" of the Université Libre de Bruxelles.
*/
struct Point {
    int x, y;
    void printPoint();

    bool operator==(const Point &other) {
        return (other.x == x and other.y == y);
    };
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
    void setSize(int size){w = size; h = size;}
};

#endif
