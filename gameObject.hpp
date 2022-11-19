#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include <string>
#include <Fl/Enumerations.H>

#include "rectangle.hpp"

class GameObject{
    Point pos;
    int boxSize = 20;
    Rectangle myRectangle;
    std::string name = "";
    
    void copyFromOther(const GameObject &other){
        pos = other.pos;
        boxSize = other.boxSize;
        myRectangle = other.myRectangle;
        name = other.name;
    }

public:
    
    GameObject(Point point, int boxSize, Fl_Color frameColor, Fl_Color fillColor, std::string name);
    GameObject(const GameObject &other);

    GameObject &operator=(const GameObject &other);

    Point getPosFltk() const;
    int getSize() const;
    Rectangle &getRectangle() ;
    std::string getName() const;

    void setPos(int &x, int &y);
    void setName(std::string newName);
    void setColor(Fl_Color newFillColor);

    void draw();
};

//class GameObject{
    //Player player;
    //Wall wall;
    //Box box;
    //Target target;
    //std::string name = "";

//public:
    ////GameObject(GameObjectType object, std::string name): object{object}, name{name}{}
    //GameObject()=default;
    //GameObject(const GameObject &other): player(other.player), wall(other.wall), box(other.box), target(other.target), name(other.name){}
    //GameObject &operator=(const GameObject other){ 
        //player = other.player; 
        //wall = other.wall; 
        //box = other.box;
        //target = other.target;
        //name = other.name;
        //return *this;
    //}
    //void push(const Player &myPlayer){ player = myPlayer; name = "player";}
    //void push(const Wall &myWall){ wall = myWall; name = "wall";}
    //void push(const Box &myBox){ box = myBox; name = "box";}
    //void push(const Target &myTarget){ target=myTarget; name="target";}
    //void push(){ name = "empty";}
    //std::string getName(){ return name;}
    //Player *getPlayer(){ return &player;}
    //Wall *getWall(){return &wall;}
    //Box *getBox(){ return &box;}
    //Target *getTarget(){return &target;}

    //void draw();

//};



#endif
