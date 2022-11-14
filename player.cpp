#include <FL/Enumerations.H>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>


#include "player.hpp"
#include "rectangle.hpp"


using namespace std;


void Player::draw(){
    player.draw();
}

void Player::move(int keyCode){
    Point tmp = this->getPos();
    if (keyCode == FL_Right or keyCode == 'd') {
        cout << "Move to the  right" << endl;
        this->setPos(tmp.x + boxSize, tmp.y);
    }else if (keyCode == FL_Left or keyCode == 'q') {
        cout << "Move to the  left" << endl;
        this->setPos(tmp.x - boxSize, tmp.y);
    }else if (keyCode == FL_Up or keyCode == 'z') {
        cout << "Move up" << endl;
        this->setPos(tmp.x, tmp.y - boxSize);
    }else if (keyCode == FL_Down or keyCode == 's') {
        cout << "Move down" << endl;
        this->setPos(tmp.x, tmp.y + boxSize);
    }
}


