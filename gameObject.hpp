#ifndef _GAMEOBJECT_HPP
#define _GAMEOBJECT_HPP

#include <string>

#include "player.hpp"
#include "wall.hpp"
#include "box.hpp"
#include "target.hpp"

class GameObject{
    Player player;
    Wall wall;
    Box box;
    Target target;
    std::string name = "";

public:
    //GameObject(GameObjectType object, std::string name): object{object}, name{name}{}
    GameObject()=default;
    GameObject(const GameObject &other): player(other.player), wall(other.wall), box(other.box), target(other.target), name(other.name){}
    GameObject &operator=(const GameObject other){ 
        player = other.player; 
        wall = other.wall; 
        box = other.box;
        target = other.target;
        name = other.name;
        return *this;
    }
    void push(const Player &myPlayer){ player = myPlayer; name = "player";}
    void push(const Wall &myWall){ wall = myWall; name = "wall";}
    void push(const Box &myBox){ box = myBox; name = "box";}
    void push(const Target &myTarget){ target=myTarget; name="target";}
    void push(){ name = "empty";}
    std::string getName(){ return name;}
    Player *getPlayer(){ return &player;}
    Wall *getWall(){return &wall;}
    Box *getBox(){ return &box;}
    Target *getTarget(){return &target;}

    void draw();

    
};

#endif
