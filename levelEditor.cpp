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
    if (isGridValid() and evenBoxAndTargets()) {
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
    submitButton = new Fl_Button(150, 70, 50, 20, "Submit");
    addButton = new Fl_Button(300, 20, 100, 30, "Add Level");
    lineInput = new Fl_Input(150, 30, 50, 20, "Number of lines: ");
    colInput = new Fl_Input(150, 50, 50, 20, "Number of columns: ");
    levelName = new Fl_Input(150, 10, 100, 20, "Name of level: ");
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
            if (Fl::event_x() <= levelName->x()+levelName->w() and Fl::event_x() >=levelName->x() 
                        and Fl::event_y() <= levelName->y()+levelName->h() and Fl::event_y() >=levelName->y()) {
                levelName->handle(event);   
            }
            else{
                canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
                this->redraw();
            }
            return 1;
    }
    return 0;
}

// bool LevelEditorWindow::checkWallAllAround() {
//     std::cout << "size=" << canvas.getCells().size() << std::endl;
//     std::cout << "lines=" << canvas.getNumberOfLines() << std::endl;
//     std::cout << "cols=" << canvas.getNumberOfColumns() << std::endl;
//     for (int i=0; i < canvas.getNumberOfColumns(); i++) {
//         if (not (canvas.getCells()[i].getCurrent() == 1)) {
//             return false;
//         }
//     } 
//     for (int i=canvas.getCells().size()-1; i >= static_cast<int>(canvas.getCells().size()-canvas.getNumberOfColumns()) ; i--) {
//         if (not (canvas.getCells()[i].getCurrent() == 1)) {
//             return false;
//         }
//     }
//     for (int i=canvas.getNumberOfLines()-1; i<=static_cast<int>(canvas.getCells().size()); i+=canvas.getNumberOfColumns()) {
//         if (not (canvas.getCells()[i].getCurrent() == 1)) {
//             return false;
//         }
//     }
//     for (int i=0; i<=static_cast<int>(canvas.getCells().size()-canvas.getNumberOfLines()+1); i+=canvas.getNumberOfColumns()) {
//         if (not (canvas.getCells()[i].getCurrent() == 1)) {
//             return false;
//         }
//     }
//     return true;
// }

bool LevelEditorWindow::onlyOnePlayer() {
    std::cout << "HEY" << std::endl;
    int count = 0;
    for (int i=0; i <= canvas.getNumberOfLines();i++){
        for (int j = 0; j <= canvas.getNumberOfColumns(); j++) {
            if (canvas.getCells()[i][j].getCurrent() == 3) {
                count++;
            }
            if (count > 1) {
                std::cout << "TOO MUCH PLAYER" << std::endl;
                return false;
            }
        }
    }
    if (count != 0) {
        return true;
    }
    std::cout << "NO PLAYER" << std::endl;
    return false;
}

bool LevelEditorWindow::evenBoxAndTargets() {
    int countBox = 0;
    int countTargets = 0;
    for (int i=0; i <= canvas.getNumberOfLines();i++) {
        for (int j=0; j <= canvas.getNumberOfColumns();j++){
            if (canvas.getCells()[i][j].getCurrent() == 4) {
                countTargets++;
            }
            else if (canvas.getCells()[i][j].getCurrent() == 2) {
                countBox++;
            }
        }
    }
    bool res = countBox >= countTargets;

    if (not res) {
        std::cout << "Not enough boxes" << std::endl;
    }
    return res;
}

bool LevelEditorWindow::isGridValid() {
    if (onlyOnePlayer()) {
        return true;
    }
    return false;
}

// void LevelEditorWindow::convertCanvaToTextFile() {
//     std::string directory = "lvls\"";
//     directory += levelName->value();
//     directory += ".txt";
//     std::ofstream fw(directory, std::ofstream::out);
//     for (int i=0; i <= canvas.getNumberOfLines();i++) {
//         for (int j=0; j <= canvas.getNumberOfColumns();j++) {
//             if (canvas.getCells()[i][j].getCurrent() == 0) {
//                 fw << " ";
//             } else if (canvas.getCells()[i][j].getCurrent() == 1) {
//                 fw << "#";
//             } else if (canvas.getCells()[i][j].getCurrent() == 2) {
//                 fw << "$";
//             } else if (canvas.getCells()[i][j].getCurrent() == 3) {
//                 fw << "@";
//             } else if (canvas.getCells()[i][j].getCurrent() == 4) {
//                 fw << ".";
//             }
//             if 
//         }
//     }
// }

// void LevelEditorWindow::addLevelToLevels() {

// }