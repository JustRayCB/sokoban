#include <fstream>
#include <iostream>
#include <string>

#include "player.hpp"
#include "gameObject.hpp"
#include "wall.hpp"
#include "box.hpp"
#include "target.hpp"


void GameObject::draw(){
        if (name == "player") {
            //std::cout << name <<  "on pos : " << player.getPos().x << ", " << player.getPos().y <<std::endl;
            player.draw();
        }else if(name == "wall"){
            //std::cout << name <<  "on pos : " << wall.getPos().x << ", " << wall.getPos().y <<std::endl;
            wall.draw();
        }else if(name == "box"){
            box.draw();
        }else if(name == "target"){
            target.draw();
        }
}





