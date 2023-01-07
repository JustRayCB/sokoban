#include "text.hpp"
#include "rectangle.hpp"
#include <FL/Enumerations.H>
#include <FL/fl_draw.H>
#include <FL/fl_types.h>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>
#include <string>

Text::Text(std::string s, Point topLeft, int fontSize, Fl_Color color) :
        s{s}, topLeft{topLeft}, fontSize{fontSize}, color{color} {}


Text::Text(Point topLeft) : topLeft{topLeft}, fontSize{20}, color{FL_BLACK}{}
std::string Text::getString(){ return s;}
void Text::setString(const std::string &newString) { s = newString; }
int Text::getFontSize() { return fontSize; }
void Text::setFontSize(int newFontSize) { fontSize = newFontSize; }
Point Text::getTopLeft() { return topLeft; }
void Text::setTopLeft(Point newTopLeft) { topLeft = newTopLeft; }

void Text::draw(){
    fl_color(color);
    fl_font(FL_HELVETICA, fontSize);
    fl_draw(s.c_str(), topLeft.x, topLeft.y);
}

