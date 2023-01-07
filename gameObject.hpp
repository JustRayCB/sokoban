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
    std::string move = ""; //current animation move
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

    /*
     * @brief: Functin that will change the frame color when the mouse is on
     * this cell
     * @param mouseLoc: X and y position of the mouse
     */
    void mouseMove(Point mouseLoc);
    /*
     * @brief: Functin that will tp the player on the cell on which the player has clicked
     * @param mouseLoc: X and y position of the mouse
     */
    Point mouseClick(Point mouseLoc);

    
    Point getPosFltk() const;
    int getSize() const;
    Rectangle &getRectangle() ;
    std::string getName() const;
    std::string whichMove() const;

    /*
     * @brief: Convert fltk coordinate into vector coordinates
     * @param vectorPos: variable where we put the result
     */
    void fltkToVector(Point &vectorPos);

    bool isWall() const;
    bool isBox() const ;
    bool isPlayer() const;
    bool isTarget() const;
    bool isEmpty() const;
    bool isTp() const;

    void setPosFltk(int x, int y);

    /*
     * @brief: When the animation has ended update the FLTK pos of the current
     * object
     */
    void setPosAfterMove();
    void setName(std::string newName);
    void setColor(Fl_Color newFillColor);
    void setFrameColor(Fl_Color newFramColor);
    void setSize(int size);
    void setMove(std::string newMove);

    /*
     * Add an animation to the current object
     */
    void addAnimation();


    bool isComplete();

    void draw();
    void drawWithoutAnimation();
};

/*
 * Those are the same class as in the tp
 */
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

  /*
   * Function that will make a translation of the cell according to a certain
   * move
   */
  Point currentTranslation();
};


#endif
