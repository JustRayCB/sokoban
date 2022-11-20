#include <iostream>
#include <string>
#include <Fl/Enumerations.H>

#include "gameObject.hpp"
#include "rectangle.hpp"


GameObject::GameObject(const Point point, const int boxSize, const Fl_Color frameColor, const Fl_Color fillColor, const std::string name):
    pos(point), boxSize(boxSize), myRectangle(point, boxSize, boxSize, frameColor, fillColor), name(name){
}


GameObject::GameObject(const GameObject &other){
    copyFromOther(other);
}

GameObject& GameObject::operator=(const GameObject &other){
    this->copyFromOther(other);
    return *this;
}

Point GameObject::getPosFltk() const{
    return pos;
}

int GameObject::getSize() const{
    return boxSize;
}

Rectangle& GameObject::getRectangle(){
    return myRectangle;
}

std::string GameObject::getName() const{
    return name;
}

void GameObject::setPos(int x, int y){
    pos.x = x; pos.y = y;
}

void GameObject::setName(std::string newName){
    name = newName;
}

void GameObject::setColor(Fl_Color newFillColor){
    getRectangle().setFillColor(newFillColor);
}


void GameObject::draw(){
    getRectangle().draw();
}



