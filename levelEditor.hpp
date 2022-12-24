#ifndef _EDITOR_HPP
#define _EDITOR_HPP


#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/fl_types.h>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <Fl/Fl_Choice.H>
#include <memory.h>

class LevelEditorWindow : public Fl_Window {
private:
    Fl_Button* submitButton;
    Fl_Input* lineInput;
    Fl_Input* colInput;
    void bouton_callback();
    static void static_bouton_callback(Fl_Widget* w, void* ptr);

 public:
    //LevelEditorWindow() : Fl_Window(000, 000, 1000, 975, "Level Editor");
    LevelEditorWindow();
    ~LevelEditorWindow(){
        std::cout << "Destroying LevelEditorWindow" << std::endl;
        delete submitButton;
        delete lineInput;
        delete colInput;
    }
};

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



void generateButtonEditor();
#endif
