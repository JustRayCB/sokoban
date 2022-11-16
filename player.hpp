#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>
#include <memory>

#include "rectangle.hpp"

//struct Point {
  //int x, y;
  //void printPoint();
//};


//class Player{
    //const int boxSize = 20;
    //Point pos;
    //Rectangle player;

//public:
    //Player(Point center={0, 0}):player(center){}
    //void draw();
    //Point getPos() const { return player.getCenter(); }
    //void setPos(int x, int y){ player.setCenter(x, y); };
    //void move(int keyCode);




//};

class Player{
    Point pos;
    int boxSize;
    Rectangle player;

    void copyFromOther(const Player &other){
        pos = other.pos;
        boxSize = other.boxSize;
        player = other.player;
        
    }
public:
    Player(Point center={0,0}, int boxSize=50): pos(center), boxSize(boxSize), player(center, boxSize, boxSize){}
    Player(const Player &other){
        copyFromOther(other);
    }
    
    Player &operator=(const Player &copy){
        copyFromOther(copy);
        return *this;
    }

    Point getPosFltk() const {return pos;}
    int getSize()const {return boxSize;}

    void setPos(int x, int y){ pos.x = x; pos.y = y;}
    void move(int keyCode);
    void draw();
    Rectangle &getRectangle(){ return player;}


};
//class Player{
    //Point pos;
    //int boxSize;
//public:
    //Player(Point center={0, 0}, int boxSize=20):pos{center}, boxSize(boxSize){}
    //Point getPos() const { return pos; }
    //void setPos(int x, int y){ pos.x = x; pos.y = y;}
    
//};

//class  PlayerControll{
    //std::shared_ptr<Player> player;
        
//public:
    //PlayerControll(std::shared_ptr<Player> player): player{player}{}
    //void move(int keyCode);

//};

//class DisplayPlayer{
    //std::shared_ptr<Player> player;
//public:
    //DisplayPlayer(std::shared_ptr<Player> player): player{player}{}
    //void draw();    
//};

//struct test{
    //std::string name;
    //Player player;
    //std::string Wall;
    //std::string Box;

    //void push(Player player){player = player;}
    //void push(std::string wall){ Wall = wall;}


//};

#endif
