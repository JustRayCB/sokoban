#include "levelEditor.hpp"
#include <cstring>
#include <iostream> // nécessaire pour std::cout

void generateButtonEditor(){
    LevelEditorWindow* editor = new LevelEditorWindow;
    editor->show();
}

void LevelEditorWindow::bouton_callback(){
    if ((atoi(lineInput->value()) > 2) and ((atoi(colInput->value()) > 2))) {
        Canvas newCanvas = Canvas(atoi(lineInput->value()), atoi(colInput->value()));
        newCanvas.setNumberOfColumns(atoi(colInput->value()));
        newCanvas.setNumberOfLines(atoi(lineInput->value()));
        this->setCanva(newCanvas);
        this->redraw();
    }
    else{
        std::cout << "WRONG DIMENSIONS" << std::endl;
    }
}
void LevelEditorWindow::adding_bouton_callback(){
    if (isGridValid()) {
        std::cout << "GOOD GRID" << std::endl;
    } else {
        std::cout << "BAD GRID" << std::endl;
    }
}

void LevelEditorWindow::static_bouton_callback(Fl_Widget* w, void* ptr){
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    me->bouton_callback();
}
void LevelEditorWindow::static_addingbouton_callback(Fl_Widget* w, void* ptr){
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    me->adding_bouton_callback();
}

LevelEditorWindow::LevelEditorWindow() : Fl_Window(000, 000, 1000, 975, "Level Editor"){
    submitButton = new Fl_Button(150, 50, 50, 20, "Submit");
    addButton = new Fl_Button(300, 20, 100, 30, "Add Level");
    lineInput = new Fl_Input(150, 30, 50, 20, "Number of lines: ");
    colInput = new Fl_Input(150, 10, 50, 20, "Number of columns: ");
    submitButton->callback(static_bouton_callback, this);
    addButton->callback(static_addingbouton_callback, this);
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
            this->redraw();
            return 1;
        case FL_PUSH:
            if (Fl::event_x() <= lineInput->x()+lineInput->w() and Fl::event_x() >=lineInput->x() 
                        and Fl::event_y() <= lineInput->y()+lineInput->h() and Fl::event_y() >=lineInput->y()) {
                lineInput->handle(event);
                
            }
            else if (Fl::event_x() <= submitButton->x()+submitButton->w() and Fl::event_x() >=submitButton->x() 
                        and Fl::event_y() <= submitButton->y()+submitButton->h() and Fl::event_y() >=submitButton->y()) {
                submitButton->do_callback();
            }
            else if (Fl::event_x() <= colInput->x()+colInput->w() and Fl::event_x() >=colInput->x() 
                        and Fl::event_y() <= colInput->y()+colInput->h() and Fl::event_y() >=colInput->y()) {
                colInput->handle(event);
            }
            else if (Fl::event_x() <= addButton->x()+addButton->w() and Fl::event_x() >=addButton->x() 
                        and Fl::event_y() <= addButton->y()+addButton->h() and Fl::event_y() >=addButton->y()) {
                addButton->do_callback();
            }
            else{
                canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
                this->redraw();
            }
            return 1;
    }
    return 0;
}

bool LevelEditorWindow::checkWallAllAround() {
    std::cout << "size=" << canvas.getCells().size() << std::endl;
    std::cout << "lines=" << canvas.getNumberOfLines() << std::endl;
    std::cout << "cols=" << canvas.getNumberOfColumns() << std::endl;
    for (int i=0; i < canvas.getNumberOfColumns(); i++) {
        if (not (canvas.getCells()[i].getCurrent() == 1)) {
            return false;
        }
    } 
    for (int i=canvas.getCells().size()-1; i >= static_cast<int>(canvas.getCells().size()-canvas.getNumberOfColumns()) ; i--) {
        if (not (canvas.getCells()[i].getCurrent() == 1)) {
            return false;
        }
    }
    for (int i=canvas.getNumberOfLines()-1; i<=static_cast<int>(canvas.getCells().size()); i+=canvas.getNumberOfColumns()) {
        if (not (canvas.getCells()[i].getCurrent() == 1)) {
            return false;
        }
    }
    for (int i=0; i<=static_cast<int>(canvas.getCells().size()-canvas.getNumberOfLines()+1); i+=canvas.getNumberOfColumns()) {
        if (not (canvas.getCells()[i].getCurrent() == 1)) {
            return false;
        }
    }
    return true;
}

bool LevelEditorWindow::onlyOnePlayer() {
    int count = 0;
    for (int i=0; i <= static_cast<int>(canvas.getCells().size());i++){
        if (canvas.getCells()[i].getCurrent() == 3) {
            count++;
        }
        if (count > 1) {
            std::cout << "TOO MUCH PLAYER" << std::endl;
            return false;
        }
    }
    if (count != 0) {
        return true;
    }
    std::cout << "NO PLAYER" << std::endl;
    return false;
}


bool LevelEditorWindow::isGridValid() {
    if (checkWallAllAround() and onlyOnePlayer()) {
        return true;
    }
    return false;
}