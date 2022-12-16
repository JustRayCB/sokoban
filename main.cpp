
// These should include everything you might use
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/fl_types.h>
#include <fstream>
#include <math.h>
#include <memory>
#include <ostream>
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


void configChoice(Fl_Choice *choice){
    std::ifstream myFile("lvls/all.txt");
    std::string line;
    if (myFile.is_open()) {
        while (myFile) {
            std::getline(myFile, line);
            choice->add(line.c_str());
        }
    }
    choice->value(0);

}

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
        configChoice(choice);
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
                    std::string fileName =  "lvls/lvl"+std::to_string(choice->value()+1)+".txt";
                    currentFile =fileName;
                    Board nboard;
                    loadBoard(nboard, fileName);
                    board = nboard;
                    stopMove = 0;
                
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
                        if (board.isGameOver()) {
                            if (board.getBestScore() > board.getStepCount() or board.getBestScore() == 0) {
                                std::cout << "New best score : " << board.getStepCount() << 
                                    " before : " << board.getBestScore() << std::endl;
                                board.setBestScore(board.getStepCount());
                                writeBestScore();
                            }
                        
                        }
                    }
                    else {
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
    ~MainWindow(){
        std::cout << "Destroying " << std::endl;
        delete choice;
    }

    void writeBestScore(){
        std::ifstream myFile(currentFile);
        std::vector<std::string> allLines;
        std::string line;
        if (myFile.is_open()) {
            while (std::getline(myFile, line)) {
                allLines.push_back(line);
            }
            myFile.close();
        }
        std::cout << allLines.at(0) << std::endl;
        allLines[0] = std::to_string(board.getNbLine()) + " " + std::to_string(board.getNbCol()) + " " + std::to_string(board.getBestScore());
        std::cout << "Got modified " << std::endl;
        std::cout << allLines.at(0) << std::endl;
        std::ofstream writeFile(currentFile);
        if (writeFile.is_open()) {
            for (auto &str : allLines) {
                writeFile << str << std::endl;
            }
        }
        writeFile.close();
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


