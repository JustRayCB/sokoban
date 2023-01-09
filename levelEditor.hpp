#ifndef _EDITOR_HPP
#define _EDITOR_HPP

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
#include <FL/fl_message.H>
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
#include <fstream>
#include <cstring>

#include "grid.hpp"

class LevelEditorWindow : public Fl_Window {
private:
    Fl_Button* submitButton;
    Fl_Button* addButton;
    Fl_Button* closeButton;
    Fl_Input* lineInput;
    Fl_Input* colInput;
    Fl_Input* movesLimit;
    void closeWindow(Fl_Window* firstWindow, Fl_Window* secondWindow);
    void submitButtonCallback();
    void addingButtonCallback();
    static void static_submitButton_callback(Fl_Widget* w, void* ptr);
    static void static_addingButton_callback(Fl_Widget* w, void* ptr);
    Canvas canvas;

 public:
    LevelEditorWindow();
    ~LevelEditorWindow() {
        delete submitButton;
        delete addButton;
        delete closeButton;
        delete lineInput;
        delete colInput;
        delete movesLimit;
    };
    void setCanva(Canvas canva);
    void draw() override;
    int handle(int event) override;

    Fl_Button* get_closeButton();
    /*
     * @brief: Function that checks if an user input grid is valid
     */
    bool isGridValid();
    /*
     * @brief: Function that checks if there's only two telportation
     * cases in the user input grid
     */
    bool onlyTwoTp();
    /*
     * @brief: Function that checks if there's only one player the user 
     * input grid
     */
    bool onlyOnePlayer();
    /*
     * @brief: Function that checks if there's the same number of target
     * cases as boxes cases there must be at least one of each
     */
    bool evenBoxAndTargets();
    /*
     * @brief: Function that converts a user input grid into a .txt file
     * so that the player can play on the created level
     */
    void convertCanvaToTextFile();
};

#endif
