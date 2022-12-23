
// These should include everything you might use
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/fl_types.h>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
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
#include "levelEditor.hpp"


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
void updateWelcomeMessageCB(void *data);



class MainWindow : public Fl_Window {
    Board board;
    DisplayBoard display;
    Controll controller;
    int stopMove = 0;
    std::string currentFile;
    Fl_Choice *choice;
    Fl_Button *reset;
    Fl_Button *lvlEditor;
    bool showMessage = true;
    Fl_Box *box;
    //Il faut un endroit ou stocker les niveaux et savoir au quel niveau on est

public:
    ~MainWindow(){
        std::cout << "Destroying " << std::endl;
        delete choice;
        delete box;
        delete reset;
    }

    MainWindow() : Fl_Window(000, 000, 1000, 975, "Sokoban") {
        Fl::add_timeout(1.0 / 60, Timer_CB, this);
        //resizable(this);
        currentFile = "lvls/lvl1.txt";
        loadBoard(board, currentFile);
        display.setBoard(&board);
        controller.setBoard(&board);
        choice = new Fl_Choice(210,120,100,30,"Levels");
        reset = new Fl_Button(310, 120, 150, 30, "Reset Best Score");
        lvlEditor = new Fl_Button(165, 60, 150, 30, "Create New Level");
        choice->hide(); reset->hide(); lvlEditor->hide();
        configChoice(choice);
        box = new Fl_Box(350,250,300,300,"Bienvenue !\n"
                "Jeu Sokoban, Créé par \nHugo Callens et"
                "\nRayan Contuliano Bravo");
        box->labelsize(26);
        box->labelfont(FL_BOLD+FL_ITALIC);
        box->labeltype(FL_SHADOW_LABEL);
        Fl::add_timeout(1.0, updateWelcomeMessageCB, this);
    }
    void updateWelcomeMessage() {
        showMessage = false;
        box->hide();
    }
    void draw() override {
        Fl_Window::draw();
        if (showMessage) {
            box->show();
        }
        else {
            display.draw();
            choice->show();
            reset->show();
            lvlEditor->show();
        }
    }

    void handleChoice(){
        choice->handle(Fl::event_button());
        currentFile =   "lvls/lvl"+std::to_string(choice->value()+1)+".txt";
        Board nboard;
        loadBoard(nboard, currentFile);
        board = nboard;
        stopMove = 0;

    }

    void resetBoard(){
        Board nboard;
        loadBoard(nboard, currentFile);
        board = nboard;
        stopMove = 0;

    }
    int handle(int event) override {
        switch (event) {
            case FL_PUSH:{

                if (Fl::event_x() <= choice->x()+choice->w() and Fl::event_x() >=choice->x() 
                        and Fl::event_y() <= choice->y()+choice->h() and Fl::event_y() >=choice->y()) {
                    handleChoice();
                }
                if (Fl::event_x() <= reset->x()+reset->w() and Fl::event_x() >=reset->x() 
                        and Fl::event_y() <= reset->y()+reset->h() and Fl::event_y() >=reset->y()) {
                    board.setBestScore(0); writeBestScore() ;
                }
                if (Fl::event_x() <= lvlEditor->x()+lvlEditor->w() and Fl::event_x() >=lvlEditor->x() 
                        and Fl::event_y() <= lvlEditor->y()+lvlEditor->h() and Fl::event_y() >=lvlEditor->y()) {
                    std::cout << "On lvlEditor" << std::endl;
                    generateButtonEditor();
                    this->hide();
                }
                return 1;

            }
            case FL_KEYDOWN:
                if (Fl::event_key() == ' ') { //reset game
                    resetBoard();
                }
                if (!stopMove) {
                    if (! board.isGameOver() and not(board.getLimit() == board.getStepCount())){ //if limit != 0
                        controller.move(Fl::event_key());    
                        if (board.isGameOver()) { newBestScore(); }
                    }
                    else { stopMove = 1; }
                }
        }
        return 0;
    }
    void newBestScore(){
        if (board.getBestScore() > board.getStepCount() or board.getBestScore() == 0) {
            std::cout << "New best score : " << board.getStepCount() << 
                " before : " << board.getBestScore() << std::endl;
            board.setBestScore(board.getStepCount());
            writeBestScore();
        }
    }
    static void Timer_CB(void *userdata) {
        MainWindow *o = (MainWindow *)userdata;
        o->redraw();
        Fl::repeat_timeout(1.0 / 120, Timer_CB, userdata);
    }

    void writeBestScore(){
        std::ifstream myFile(currentFile);
        std::vector<std::string> allLines;
        std::string line;
        if (myFile.is_open()) {
            while (std::getline(myFile, line)) { allLines.push_back(line); }
            myFile.close();
        }
        allLines[0] = std::to_string(board.getNbLine()) + " " + 
            std::to_string(board.getNbCol()) + " " + std::to_string(board.getBestScore())
            + std::to_string(board.getLimit());
        std::ofstream writeFile(currentFile);
        if (writeFile.is_open()) {
            for (auto &str : allLines) { writeFile << str << std::endl; }
        }
        writeFile.close();
    }
};

void updateWelcomeMessageCB(void *data) {
    MainWindow *window = static_cast<MainWindow*>(data);
    window->updateWelcomeMessage();
}

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


