
// These should include everything you might use
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <math.h>
#include <memory>
#include <time.h>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <memory.h>

#include "player.hpp"
#include "board.hpp"

using namespace std;


class MainWindow : public Fl_Window {
    //const int windowWidth = 1000;
    //const int windowHeight = 975;
    //const double refreshPerSecond = 60;
    //Player player{{500, 500}};    
    //shared_ptr<Board> board;
    Board board;
    DisplayBoard displayBoard;
    Controll controller;

public:
    MainWindow() : Fl_Window(000, 000, 1000, 975, "Sokoban") {
        Fl::add_timeout(1.0 / 60, Timer_CB, this);
        resizable(this);
        loadBoard(board, "test.txt");
        displayBoard.setBoard(&board);
        controller.setBoard(&board);

    }
    void draw() override {
        Fl_Window::draw();
        displayBoard.draw();
        //board.draw();
    }
    int handle(int event) override {
        switch (event) {
            //case FL_PUSH:
                //canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
                //return 1;
            //case FL_KEYDOWN:
                //canvas.keyPressed(Fl::event_key());
                //return 1;
            case FL_KEYDOWN:
                ////keyPressed(Fl::event_key());
                ////player.move(Fl::event_key());
                controller.move(Fl::event_key());
        }
        return 0;
    }
    static void Timer_CB(void *userdata) {
        MainWindow *o = (MainWindow *)userdata;
        o->redraw();
        Fl::repeat_timeout(1.0 / 60, Timer_CB, userdata);
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

