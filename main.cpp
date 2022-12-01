
// These should include everything you might use
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/fl_types.h>
#include <math.h>
#include <memory>
#include <time.h>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <Fl/Fl_Choice.H>
#include <memory.h>

#include "board.hpp"
#include "display.hpp"
#include "controller.hpp"

using namespace std;


class MainWindow : public Fl_Window {
    Board board;
    DisplayBoard display;
    Controll controller;
    int stopMove = 0;
    std::string currentFile;
    Fl_Choice *choice;
    //Il faut un endroit ou stocker les niveaux et savoir au quel niveau on est

public:
    MainWindow() : Fl_Window(000, 000, 1000, 975, "Sokoban") {
        Fl::add_timeout(1.0 / 60, Timer_CB, this);
        //resizable(this);
        currentFile = "lvls/lvl1.txt";
        loadBoard(board, currentFile);
        display.setBoard(&board);
        controller.setBoard(&board);
        choice = new Fl_Choice(210,120,100,30,"Levels");

        choice->add("lvl1");
        choice->add("lvl2");
        choice->add("lvl3");
        choice->value(0);
    }
    void draw() override {
        Fl_Window::draw();
        display.draw();
        Fl_Widget *ptr = choice;
        ptr->draw();
    }
    void callHandle(int event){
        choice->handle(event);
        
    }
    int handle(int event) override {
        switch (event) {
            case FL_PUSH:{

                if (Fl::event_x() <= choice->x()+choice->w() and Fl::event_x() >=choice->x() 
                        and Fl::event_y() <= choice->y()+choice->h() and Fl::event_y() >=choice->y()) {
                    choice->handle(Fl::event_button());
                    string fileName =  "lvls/lvl"+to_string(choice->value()+1)+".txt";
                    currentFile =fileName;
                    Board nboard;
                    loadBoard(nboard, fileName);
                    board = nboard;
                
                }

                return 1;

            }
            case FL_KEYDOWN:
                if (Fl::event_key() == ' ') {
                    Board nboard;
                    loadBoard(nboard, currentFile);
                    board = nboard;
                    stopMove = 0;
                }
                if (!stopMove) {
                    if (! board.isGameOver()){
                        controller.move(Fl::event_key());    
                    }
                    else {
                        // if bestScore > stepCount{
                        //  saveBestScore();
                        //}
                        stopMove = 1;
                        return 1;
                    }
                }
        }
        return 0;
    }
    static void Timer_CB(void *userdata) {
        MainWindow *o = (MainWindow *)userdata;
        o->redraw();
        Fl::repeat_timeout(1.0 / 120, Timer_CB, userdata);
    }
};

/*--------------------------------------------------

main

Do not edit!!!!

--------------------------------------------------*/



int main(int argc, char *argv[]) {
    srand(time(0));
    MainWindow window;
    window.show(argc, argv);
    return Fl::run();
}


