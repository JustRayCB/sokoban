
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

#include "board.hpp"
#include "display.hpp"
#include "controller.hpp"

using namespace std;


class MainWindow : public Fl_Window {
    Board board;
    DisplayBoard display;
    Controll controller;
    int stopMove = 0;
    //Il faut un endroit ou stocker les niveaux et savoir au quel niveau on est

public:
    MainWindow() : Fl_Window(000, 000, 1000, 975, "Sokoban") {
        Fl::add_timeout(1.0 / 60, Timer_CB, this);
        resizable(this);
        loadBoard(board, "test.txt");
        display.setBoard(&board);
        controller.setBoard(&board);
    }
    void draw() override {
        Fl_Window::draw();
        display.draw();
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
                if (!stopMove) {
                    if (! board.isGameOver()){
                        controller.move(Fl::event_key());    
                    }
                    else {
                        // J'ai mis !stopMove pcq sinn il rentre tjrs là
                        // et la condition !board.isGameOver() est toujous
                        // évaluée Save best Score
                        // if bestScore > stepCount{
                        //  saveBestScore();
                        //}
                        return 1;
                    }
                }
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


