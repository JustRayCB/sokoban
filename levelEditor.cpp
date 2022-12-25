#include "levelEditor.hpp"
#include <cstring>
#include <iostream> // nécessaire pour std::cout

void generateButtonEditor(){
    LevelEditorWindow* editor = new LevelEditorWindow;
    editor->show();
}

void LevelEditorWindow::bouton_callback(){
    std::cout << "Hi" << std::endl;
    std::cout << "Number of lines: " << lineInput->value() << std::endl;
    std::cout << "Number of columns: " << colInput->value() << std::endl;
}

void LevelEditorWindow::static_bouton_callback(Fl_Widget* w, void* ptr){
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    me->bouton_callback();
}

LevelEditorWindow::LevelEditorWindow() : Fl_Window(000, 000, 1000, 975, "Level Editor"){
    submitButton = new Fl_Button(150, 50, 50, 20, "Submit");
    lineInput = new Fl_Input(150, 30, 50, 20, "Number of lines: ");
    colInput = new Fl_Input(150, 10, 50, 20, "Number of columns: ");
    submitButton->callback(static_bouton_callback, this);
    end();
    show();
}
