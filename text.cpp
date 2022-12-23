#include "text.hpp"
#include "rectangle.hpp"
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <FL/fl_types.h>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>
#include <string>

Text::Text(std::string s, Point center, int fontSize, Fl_Color color):
    s{s}, center{center}, fontSize{fontSize}, color{color} {}

Text::Text(Point center):center{center}, fontSize(20), color{FL_BLACK}{}
std::string Text::getString(){ return s;}
void Text::setString(const std::string &newString) { s = newString; }
int Text::getFontSize() { return fontSize; }
void Text::setFontSize(int newFontSize) { fontSize = newFontSize; }
Point Text::getCenter() { return center; }
void Text::setCenter(Point newCenter) { center = newCenter; }

void Text::draw(){
    fl_color(color);
    fl_font(FL_HELVETICA, fontSize);
    int width, height;
    fl_measure(s.c_str(), width, height, false);
    fl_draw(s.c_str(), center.x-width/2, center.y-fl_descent()+height/2);
}

