#include <fstream>
#include <iostream>
#include <string>

#include "player.hpp"
#include "gameObject.hpp"
#include "wall.hpp"
//#include "box.hpp"


void GameObject::draw(){
        if (name == "player") {
            //std::cout << name <<  "on pos : " << player.getPos().x << ", " << player.getPos().y <<std::endl;
            player.draw();
        }else if(name == "wall"){
            //std::cout << name <<  "on pos : " << wall.getPos().x << ", " << wall.getPos().y <<std::endl;
            wall.draw();
        }//elif(name == "box"){
            //box.draw();
        //}
}





