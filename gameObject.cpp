#include <iostream>
#include <string>
#include <Fl/Enumerations.H>
#include <unistd.h>

#include "gameObject.hpp"
#include "rectangle.hpp"


GameObject::GameObject(const Point point, const int boxSize, const Fl_Color frameColor, const Fl_Color fillColor, const std::string name):
    pos(point), boxSize(boxSize), myRectangle(point, boxSize, boxSize, frameColor, fillColor), name(name){
}


GameObject::GameObject(const GameObject &other){
    copyFromOther(other);
}

void GameObject::mouseMove(Point mouseLoc) {
    if (myRectangle.contains(mouseLoc)) {
        myRectangle.setFrameColor(FL_RED);
    } else {
        if (name == "empty"){
            myRectangle.setFrameColor(FL_GRAY);
        } else {
            myRectangle.setFrameColor(FL_BLACK);
        }
    }
}
void GameObject::mouseClick(Point mouseLoc) { 
    if (myRectangle.contains(mouseLoc)) {
        int x, y;
        x = (pos.y - 200) / boxSize;
        y = (pos.x - 200) / boxSize;
        std::cout << "(" << x << "," << y << ")" << "\n";
    }
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

std::string GameObject::whichMove() const{
    return move;
}

bool GameObject::isBox() const{ return name == "box"; }
bool GameObject::isWall() const{ return name == "wall"; }
bool GameObject::isPlayer() const{ return name == "player"; }
bool GameObject::isTarget() const{ return name == "target"; }
bool GameObject::isEmpty() const{ return name == "empty"; }

void GameObject::setPosFltk(int x, int y){
    pos.x = x; pos.y = y;
    myRectangle.setCenter(pos);
}

void GameObject::setPosAfterMove(){
    int x = pos.x, y = pos.y;
    if (move == "up") { x = pos.x, y = pos.y - boxSize;}
    if (move == "down") { x = pos.x, y = pos.y + boxSize;}
    if (move == "left") { x = pos.x - boxSize, y = pos.y;}
    if (move == "right") { x = pos.x + boxSize, y = pos.y;}
    setPosFltk(x, y);
}


void GameObject::setName(std::string newName){
    name = newName;
}

void GameObject::setColor(Fl_Color newFillColor){
    getRectangle().setFillColor(newFillColor);
}

void GameObject::setSize(int size) {
    boxSize = size;
    getRectangle().setSize(size);
}

void GameObject::setMove(std::string newMove){
    move = newMove;
}

void GameObject::addAnimation(){
    if (not animation) {
        animation = new Animation(this, move);
    }
}

bool GameObject::isComplete(){
    if (animation) {
        return animation->isComplete();
    }
    return true;
}


void GameObject::drawWithoutAnimation(){
    myRectangle.draw();
}
void GameObject::draw(){
    if (animation and animation->isComplete()) {
        delete animation;
        animation = nullptr;
        setPosAfterMove();
    }
    if (animation){
        animation->draw();
    }
    else{
        drawWithoutAnimation();
    }
}


bool Animation::isComplete() { return time > duration; }

void Animation::draw() {
  ++time;
  Translation t3{currentTranslation()};
  c->drawWithoutAnimation();
}
Point Animation::currentTranslation() {
    double speed = static_cast<float>(c->getSize())/ duration; // vitesse de translation en pixels par seconde
    if (move == "up"){
      return {0, -static_cast<int>(speed * time)}; // translation vers le haut de speed pixels par seconde
    }
    else if (move == "down"){
      return {0, static_cast<int>(speed * time)}; // translation vers le haut de speed pixels par seconde
    }
    else if (move == "left"){
      return {-static_cast<int>(speed * time), 0}; // translation vers le haut de speed pixels par seconde
    }
    else{
      return {static_cast<int>(speed * time), 0}; // translation vers le haut de speed pixels par seconde
    }
}


