#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include <string>
#include <Fl/Enumerations.H>

#include "rectangle.hpp"

class Animation;

class GameObject{
    Point pos;
    int boxSize = 20;
    Rectangle myRectangle;
    std::string name = "";
    std::string move = "";
    Animation *animation = nullptr;

    
    void copyFromOther(const GameObject &other){
        pos = other.pos;
        boxSize = other.boxSize;
        myRectangle = other.myRectangle;
        name = other.name;
        move = other.move;
        animation = other.animation;

    }

public:
    
    GameObject(const Point point, const int boxSize, const Fl_Color frameColor, const Fl_Color fillColor, const std::string name);
    GameObject()=default;
    GameObject(const GameObject &other);

    GameObject &operator=(const GameObject &other);

    void mouseMove(Point mouseLoc);
    std::string mouseClick(Point mouseLoc);

    Point getPosFltk() const;
    int getSize() const;
    Rectangle &getRectangle() ;
    std::string getName() const;
    std::string whichMove() const;
    bool isWall() const;
    bool isBox() const ;
    bool isPlayer() const;
    bool isTarget() const;
    bool isEmpty() const;

    void setPosFltk(int x, int y);
    void setPosAfterMove();
    void setName(std::string newName);
    void setColor(Fl_Color newFillColor);
    void setSize(int size);
    void setMove(std::string newMove);
    void addAnimation();


    bool isComplete();

    void draw();
    void drawWithoutAnimation();
};


struct Translation {
  Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() { fl_pop_matrix(); }
};


class Animation {
 private:
  const int     duration     = 10;
  int           time{0};
  GameObject *c;
  std::string move = "";

 public:
  Animation(GameObject *cellToAnimate, std::string move) : c{cellToAnimate}, move{move} {}
  void draw();
  bool isComplete();
  Point currentTranslation();
};


#endif
