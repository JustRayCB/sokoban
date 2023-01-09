#include "levelEditor.hpp"

LevelEditorWindow::LevelEditorWindow() : Fl_Window(000, 000, 1000, 975, "Level Editor"){
    submitButton = new Fl_Button(150, 90, 50, 20, "Submit");
    addButton = new Fl_Button(300, 20, 100, 30, "Add Level");
    closeButton = new Fl_Button(300, 50, 100, 30, "Return to game");
    lineInput = new Fl_Input(150, 30, 50, 20, "Number of lines: ");
    colInput = new Fl_Input(150, 50, 50, 20, "Number of columns: ");
    movesLimit = new Fl_Input(150, 70, 50, 20, "Maximum moves: ");
    submitButton->callback(static_submitButton_callback, this);
    addButton->callback(static_addingButton_callback, this);
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
            else if (Fl::event_x() <= movesLimit->x()+movesLimit->w() and Fl::event_x() >=movesLimit->x() 
                        and Fl::event_y() <= movesLimit->y()+movesLimit->h() and Fl::event_y() >=movesLimit->y()) {
                movesLimit->handle(event);   
            }
            else if (Fl::event_x() <= closeButton->x()+closeButton->w() and Fl::event_x() >=closeButton->x() 
                        and Fl::event_y() <= closeButton->y()+closeButton->h() and Fl::event_y() >=closeButton->y()) {
                closeButton->do_callback();
            }
            else{
                canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
                this->redraw();
            }
            return 1;
    }
    return 0;
}

bool LevelEditorWindow::isGridValid() {
    return checkCorrectGrid();
}

bool LevelEditorWindow::checkCorrectGrid(){
    int countPlayer = 0;
    int countBox = 0;
    int countTargets = 0;
    int countTp = 0;
    for (auto &line : canvas.getCells()) {
        for (auto &elem : line) {
            if (elem.getCurrent() == 5) {
                countTp++;
            }
            if (elem.getCurrent() == 3) {
                countPlayer++;
            }
            if (elem.getCurrent() == 4) {
                countTargets++;
            }
            if (elem.getCurrent() == 2) {
                countBox++;
            }
        }
    }
    bool res = countBox >= countTargets and countBox != 0 and countTargets != 0;
    if (not res) {
        fl_alert("There is not enough boxes in comparaison of targets. Need to be at least 1 box and 1 target.");
        return false;
    }
    if (countTp > 2) {
        fl_alert("You placed too much teleportation cells, the max is 2.");
        return false;
    }
    if (countPlayer > 1) {
        fl_alert("There is too much player, only one player is admitted.");
        return false;
    }
    if (countPlayer == 0) {
        fl_alert("You should place the player !");
        return false;
    }
    return true;
}

void LevelEditorWindow::convertCanvaToTextFile() {
    std::ifstream allRead("lvls/all.txt");
    std::string line;
    int counter = 0;
    while(std::getline(allRead, line)) {
        counter++;
    }
    
    std::string filingName = "lvl" + std::to_string(counter+1);
    std::string directory = "lvls/" + filingName + ".txt";

    std::ofstream fw(directory, std::ofstream::out);
    const char* maxMoveInputValue = movesLimit->value();
    std::string limit;
    if(maxMoveInputValue != 0 && strlen(maxMoveInputValue) !=0) {
        limit = movesLimit->value();
    } else {
        limit = "50";
    }

    fw << canvas.getNumberOfLines() << " " << canvas.getNumberOfColumns() << " 0 " << limit << "\n";
    for (auto &line : canvas.getCells()) {
        for (auto &elem : line) {
            if (elem.getCurrent() == 0) {
                fw << " ";
            } else if (elem.getCurrent() == 1) {
                fw << "#";
            } else if (elem.getCurrent() == 2) {
                fw << "$";
            } else if (elem.getCurrent() == 3) {
                fw << "@";
            } else if (elem.getCurrent() == 4) {
                fw << ".";
            } else if (elem.getCurrent() == 5) {
                fw << "/";
            }
        }
        fw << "\n";
    }
    std::ofstream allWrite("lvls/all.txt", std::ofstream::app);
    allWrite << filingName << "\n";
    fl_alert("File added as : %s", filingName.c_str());
}

void LevelEditorWindow::static_submitButton_callback(Fl_Widget* w, void* ptr){
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    me->submitButtonCallback();
}

void LevelEditorWindow::static_addingButton_callback(Fl_Widget* w, void* ptr){
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    me->addingButtonCallback();
}

void LevelEditorWindow::submitButtonCallback(){
    if ((atoi(lineInput->value()) > 2) and ((atoi(colInput->value()) > 2))) {
        Canvas newCanvas = Canvas(atoi(colInput->value()),atoi(lineInput->value()));
        newCanvas.setNumberOfColumns(atoi(colInput->value()));
        newCanvas.setNumberOfLines(atoi(lineInput->value()));
        this->setCanva(newCanvas);
        this->redraw();
    }
    else{
        fl_alert("You introduced bad dimensions, must be integers and greater than 2.");
    }
}

void LevelEditorWindow::addingButtonCallback(){
    if (isGridValid()) {
        convertCanvaToTextFile();
    }
}

Fl_Button* LevelEditorWindow::get_closeButton() {
    return closeButton;
}

void LevelEditorWindow::closeWindow(Fl_Window* firstWindow, Fl_Window* secondWindow) {
    secondWindow->hide();
    firstWindow->show();
    firstWindow->redraw();
}
