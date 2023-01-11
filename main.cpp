
// These should include everything you might use
#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_ask.H>
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
#include <unistd.h>

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

void configHello(Fl_Box *hello){
    hello->labelsize(26);
    hello->labelfont(FL_BOLD+FL_ITALIC);
    hello->labeltype(FL_SHADOW_LABEL);

}

class MainWindow : public Fl_Window {
    Board board;
    DisplayBoard display;
    Controll controller;
    int stopMove = 0;
    std::string currentFile;
    Fl_Choice *choice;
    Fl_Button *reset;
    Fl_Button *lvlEditor;
    Fl_Button *lvlEditEditor;
    bool showMessage = true;
    Fl_Box *hello;
    // static void open_second_window(Fl_Widget* widget, void* data);
    // static void close_second_window(Fl_Widget* widget, void* data);
    //Il faut un endroit ou stocker les niveaux et savoir au quel niveau on est

public:
    ~MainWindow(){
        std::cout << "Destroying " << std::endl;
        delete choice;
        delete hello;
        delete reset;
        delete lvlEditor;
        delete lvlEditEditor;
    }

    MainWindow() : Fl_Window(000, 000, 1000, 975, "Sokoban") {
        Fl::add_timeout(1.0 / 60, Timer_CB, this);
        //resizable(this);
        currentFile = "lvls/lvl1.txt";
        loadBoard(board, currentFile);
        display.setBoard(&board);
        controller.setBoard(&board);
        reset = new Fl_Button(310, 120, 150, 30, "Reset Best Score");
        lvlEditor = new Fl_Button(165, 60, 150, 30, "Create New Level");
        lvlEditor->callback(open_second_window, this);
        lvlEditEditor = new Fl_Button(165, 30, 150, 30, "Edit this level");
        lvlEditEditor->callback(edit_second_window, this);
        choice = new Fl_Choice(210,120,100,30,"Levels");
        choice->hide(); reset->hide(); lvlEditor->hide(); lvlEditEditor->hide();
        configChoice(choice);
        hello = new Fl_Box(350,250,300,300,"Bienvenue !\n"
                            "Jeu Sokoban, Créé par \nHugo Callens et"
                            "\nRayan Contuliano Bravo");
        configHello(hello);
        Fl::add_timeout(1.0, updateWelcomeMessage, this);
    }
    static void updateWelcomeMessage(void *window) {
        MainWindow* firstWindow = (MainWindow*) window;
        firstWindow->showMessage = false;
        firstWindow->hello->hide();
    }
    void draw() override {
        Fl_Window::draw();
        if (showMessage) {
            hello->show();
        }
        else {
            display.draw();
            choice->show();
            reset->show();
            lvlEditor->show();
            lvlEditEditor->show();
        }
    }

    static void close_second_window(Fl_Widget* widget, void* data) {
        MainWindow* firstWindow = (MainWindow*) data;
        LevelEditorWindow* secondWindow = (LevelEditorWindow*) widget->window();
        secondWindow->hide();
        configChoice(firstWindow->choice);
        std::string addedLevel = "lvls/"+static_cast<std::string>(firstWindow->choice->text(firstWindow->choice->size()-2))+".txt";
        std::cout << addedLevel << std::endl;
        firstWindow->choice->value(firstWindow->choice->size()-2);
        Board newBoard;
        loadBoard(newBoard, addedLevel);
        firstWindow->currentFile = addedLevel;
        firstWindow->setBoard(newBoard);
        firstWindow->redraw();
        firstWindow->show();
        delete secondWindow;
    }

    Board getBoard() {
        return board;
    }

    void setBoard(Board newBoard) {
        board = newBoard;
    }
    

    static void open_second_window(Fl_Widget* widget, void* data) {
        MainWindow* firstWindow = (MainWindow*) data;
        LevelEditorWindow* secondWindow = new LevelEditorWindow;
        Fl_Button* test = secondWindow->get_closeButton();
        test->callback(close_second_window, firstWindow);
        secondWindow->show();
        firstWindow->hide();
    }

    static void edit_second_window(Fl_Widget* w, void* data) {
        MainWindow* firstWindow = (MainWindow*) data;
        LevelEditorWindow* secondWindow = new LevelEditorWindow(firstWindow->currentFile, firstWindow->board);
        Fl_Button* test = secondWindow->get_closeButton();
        test->callback(close_second_window, firstWindow);
        secondWindow->show();
        firstWindow->hide();
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
            case FL_MOVE:
                controller.mouseMove(Point{Fl::event_x(), Fl::event_y()});
                this->redraw();
                return 1;
            case FL_PUSH:{

                if (Fl::event_x() <= choice->x()+choice->w() and Fl::event_x() >=choice->x() 
                        and Fl::event_y() <= choice->y()+choice->h() and Fl::event_y() >=choice->y()) {
                    handleChoice();
                }
                else if (Fl::event_x() <= reset->x()+reset->w() and Fl::event_x() >=reset->x() 
                        and Fl::event_y() <= reset->y()+reset->h() and Fl::event_y() >=reset->y()) {
                    board.setBestScore(0); writeBestScore() ;
                }
                else if (Fl::event_x() <= lvlEditor->x()+lvlEditor->w() and Fl::event_x() >=lvlEditor->x() 
                        and Fl::event_y() <= lvlEditor->y()+lvlEditor->h() and Fl::event_y() >=lvlEditor->y()) {
                    lvlEditor->do_callback();
                }
                else if (Fl::event_x() <= lvlEditEditor->x()+lvlEditEditor->w() and Fl::event_x() >=lvlEditEditor->x() 
                        and Fl::event_y() <= lvlEditEditor->y()+lvlEditEditor->h() and Fl::event_y() >=lvlEditEditor->y()) {
                    lvlEditEditor->do_callback();
                }
                else {
                    if(!stopMove) controller.moveWithMouse(Fl::event_x(), Fl::event_y());
                }
                return 1;

            }
            case FL_KEYDOWN:
                if (Fl::event_key() == ' ') { //reset game
                    resetBoard();
                }
                if (!stopMove) {
                    if (! board.isGameOver()){ //if limit != 0
                        controller.move(Fl::event_key());    
                        if (board.hasWon()) { newBestScore(); stopMove = 1;}
                    }
                    else {
                        fl_alert("GAME OVER");
                        stopMove = 1; }
                }
        }
        return 0;
    }
    void newBestScore(){
        if (board.getBestScore() > board.getStepCount() or board.getBestScore() == 0) {
            fl_alert("Congrats, you have a new best score ");
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
            std::to_string(board.getNbCol()) + " " + std::to_string(board.getBestScore()) + " "
            + std::to_string(board.getLimit()); //remake the first line pattern of all lvl files
        std::ofstream writeFile(currentFile);
        if (writeFile.is_open()) {
            for (auto &str : allLines) { writeFile << str << std::endl; }
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


