#include "levelEditor.hpp"
#include <cstring>
#include <iostream> // nécessaire pour std::cout

void generateButtonEditor(){
    LevelEditorWindow* editor = new LevelEditorWindow;
    editor->show();
}

void LevelEditorWindow::bouton_callback(){
    int test1 = atoi(lineInput->value());
    int test2 = atoi(colInput->value());
    Canvas newCanvas = Canvas(atoi(colInput->value()), atoi(lineInput->value()));
    this->setCanva(newCanvas);
    this->redraw();
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

void LevelEditorWindow::setCanva(Canvas canva){
    canvas = canva;
}

void LevelEditorWindow::draw() {
    Fl_Window::draw();
    canvas.draw();
}

int LevelEditorWindow::handle(int event) {
    switch(event) {
        case FL_MOVE:
            canvas.mouseMove(Point{Fl::event_x(), Fl::event_y()});
            return 1;
        case FL_PUSH:
            canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
            return 1;
    }
    return 0;
}
