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
    virtual ~LevelEditorWindow() {};
};

void LevelEditorWindow::bouton_callback(){
    printf("%s", colInput->value());
    printf("%s", lineInput->value());
}

void LevelEditorWindow::static_bouton_callback(Fl_Widget* w, void* ptr){
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    me->bouton_callback();
}

LevelEditorWindow::LevelEditorWindow() : Fl_Window(1000, 975, "Editor"){
    submitButton = new Fl_Button(150, 50, 50, 20, "Submit");
    lineInput = new Fl_Input(150, 30, 50, 20, "Number of lines: ");
    colInput = new Fl_Input(150, 10, 50, 20, "Number of columns: ");
    submitButton->callback(static_bouton_callback, this);
    end();
    show();
}
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
<<<<<<< HEAD


=======
>>>>>>> 77966dc (New LevelEditorWindow)

void generateButtonEditor();
#endif
