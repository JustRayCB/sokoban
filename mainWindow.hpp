#ifndef _MAINWINDOW_HPP
#define _MAINWINDOW_HPP

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

#include "board.hpp"
#include "display.hpp"
#include "controller.hpp"
#include "levelEditor.hpp"


class MainWindow: public Fl_Window{
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
    static void Timer_CB(void *userdata);
    static void updateWelcomeMessage(void *window);
    static void closeSecondWindow(Fl_Widget* widget, void* data);
    static void openSecondWindow(Fl_Widget* widget, void* data);
    static void editSecondWindow(Fl_Widget* w, void* data);

public:
    ~MainWindow(){
        std::cout << "Destroying " << std::endl;
        delete choice;
        delete hello;
        delete reset;
        delete lvlEditor;
        delete lvlEditEditor;
    }
    MainWindow();

    void draw() override;
    int handle(int event) override;


    Board getBoard();
    void setBoard(Board newBoard);
    void resetBoard();

    void handleChoice();

    bool hasWon();
    bool gameOver();

    void writeBestScore();
    void newBestScore();
};


void configChoice(Fl_Choice *choice);
void configHello(Fl_Box *hello);


#endif
