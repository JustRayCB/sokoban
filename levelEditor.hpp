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

#include "grid.hpp"

class LevelEditorWindow : public Fl_Window {
private:
    Fl_Button* submitButton;
    Fl_Button* addButton;
    Fl_Input* lineInput;
    Fl_Input* colInput;
    Fl_Input* levelName;
    Fl_Input* movesLimit;
    void bouton_callback();
    void adding_bouton_callback();
    static void static_bouton_callback(Fl_Widget* w, void* ptr);
    static void static_addingbouton_callback(Fl_Widget* w, void* ptr);
    Canvas canvas;

 public:
    //LevelEditorWindow() : Fl_Window(000, 000, 1000, 975, "Level Editor");
    LevelEditorWindow();
    virtual ~LevelEditorWindow() {};
    void setCanva(Canvas canva);
    void draw() override; 
    int handle(int event) override;

    bool isGridValid();
    bool onlyOnePlayer();
    bool evenBoxAndTargets();

    void addLevelToLevels();
    void convertCanvaToTextFile();
    // bool checkWallAllAround();
};

//void LevelEditorWindow::bouton_callback(){
    //printf("%s", colInput->value());
    //printf("%s", lineInput->value());
//}

//void LevelEditorWindow::static_bouton_callback(Fl_Widget* w, void* ptr){
    //LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    //me->bouton_callback();
//}

//LevelEditorWindow::LevelEditorWindow() : Fl_Window(1000, 975, "Editor"){
    //submitButton = new Fl_Button(150, 50, 50, 20, "Submit");
    //lineInput = new Fl_Input(150, 30, 50, 20, "Number of lines: ");
    //colInput = new Fl_Input(150, 10, 50, 20, "Number of columns: ");
    //submitButton->callback(static_bouton_callback, this);
    //end();
    //show();
//}
    // int handle(int event) override {
    //     switch(event) {
    //         case FL_PUSH:{
    //             std::cout << "PUSHING" << std::endl;
    //             std::cout << Fl::event_x() << submitButton->x() << std::endl;
    //             if (Fl::event_x() <= submitButton->x()+submitButton->w() and Fl::event_x() >= submitButton->x()
    //                     and Fl::event_y() <= submitButton->y()+submitButton->h() and Fl::event_y() >= submitButton->y()) {
    //                 std::cout << lineInput->value() << std::endl;
    //                 std::cout << colInput->value() << std::endl;
    //                 std::cout << "IM" << std::endl;
    //             }
    //             if (Fl::event_x() <= colInput->x()+colInput->w() and Fl::event_x() >= colInput->x()
    //                     and Fl::event_y() <= colInput->y()+colInput->h() and Fl::event_y() >= colInput->y()) {
    //                 colInput
    //             }
    //             return 1;
    //         }
    //     }
    //     return 0;
    // }
#endif
