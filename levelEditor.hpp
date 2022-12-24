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

void test_callback(Fl_Widget*, void *data){
    //std::cout << colInput << std::endl;
    //std::cout << lineInput << std::endl;
    std::cout << "test" << std::endl;
}   

class LevelEditorWindow : public Fl_Window {
    Fl_Button* submitButton;
    Fl_Input* lineInput;
    Fl_Input* colInput;

 public:
    ~LevelEditorWindow(){
        std::cout << "Destroying LevelEditorWindow" << std::endl;
        delete submitButton;
        delete lineInput;
        delete colInput;
    }
    LevelEditorWindow() : Fl_Window(000, 000, 1000, 975, "Level Editor") {
        std::cout << "Welcome" << std::endl;
        colInput = new Fl_Input (150, 10, 50, 20, "Number of columns: ");
        lineInput = new Fl_Input (150, 30, 50, 20, "Number of lines: ");
        submitButton = new Fl_Button(150, 50, 50, 20, "Submit");
        colInput->show(); lineInput->show(); submitButton->show();
        submitButton->callback(test_callback);
    }

    int handle(int event) override {
        switch(event) {
            case FL_PUSH:{
                std::cout << "PUSHING" << std::endl;
                std::cout << Fl::event_x() << submitButton->x() << std::endl;
                if (Fl::event_x() <= submitButton->x()+submitButton->w() and Fl::event_x() >= submitButton->x()
                        and Fl::event_y() <= submitButton->y()+submitButton->h() and Fl::event_y() >= submitButton->y()) {
                    std::cout << lineInput->value() << std::endl;
                    std::cout << colInput->value() << std::endl;
                    std::cout << "IM" << std::endl;
                }
                return 1;
            }
        }
        return 0;
    }
};

void generateButtonEditor();
#endif
