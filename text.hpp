#ifndef _TEXT_HPP
#define _TEXT_HPP
#include "rectangle.hpp"
#include <string>
class Text {
  std::string s;
  Point center;
  int fontSize;
  Fl_Color color;

 public:
  // Constructor

  Text(std::string s, Point center, int fontSize = 20, Fl_Color color = FL_BLACK);
  Text()=default;
  Text(Point center);
  // Draw
  void draw();

  // Setters and getters
  std::string getString();

  void setString(const std::string &newString);
  int getFontSize();
  void setFontSize(int newFontSize);
  Point getCenter();
  void setCenter(Point newCenter);
};
#endif
