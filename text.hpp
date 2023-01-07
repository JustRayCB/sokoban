#ifndef _TEXT_HPP
#define _TEXT_HPP
#include "rectangle.hpp"
#include <string>
class Text {
    std::string s;
    Point topLeft;
    int fontSize;
    Fl_Color color;
public:
    Text(std::string s, Point topLeft, int fontSize=20, Fl_Color color=FL_BLACK);

    Text(Point topLeft);

    std::string getString();
    void setString(const std::string &newString);
    int getFontSize();
    void setFontSize(int newFontSize);
    Point getTopLeft();
    void setTopLeft(Point newTopLeft);

    void draw();
};
#endif
