#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

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
  Point center;
  const int w = 20, h=20;
  Fl_Color fillColor, frameColor;

public:
  Rectangle(Point center, int w=20, int h=20, Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE);
  void draw();
  void setFillColor(Fl_Color newFillColor);
  void setFrameColor(Fl_Color newFrameColor);
  bool contains(Point p);
  Point getCenter() const { return center; }
  void setCenter(int &x, int &y){ center.x = x; center.y = y;}
};

#endif
