#include "levelEditor.hpp"
#include <fstream>
#include "text.hpp"
#define STARTDISPLAYX (800)
#define STARTDISPLAYY (200)

LevelEditorWindow::LevelEditorWindow() : Fl_Window(000, 000, 1000, 975, "Level Editor"){
    submitButton = new Fl_Button(150, 90, 50, 20, "Submit");
    replaceButton = new Fl_Button(300, 20, 120, 30, "Replace level");
    addButton = new Fl_Button(300, 50, 120, 30, "Add as new level");
    closeButton = new Fl_Button(300, 80, 120, 30, "Return to game");
    lineInput = new Fl_Input(150, 30, 50, 20, "Number of lines: ");
    colInput = new Fl_Input(150, 50, 50, 20, "Number of columns: ");
    movesLimit = new Fl_Input(150, 70, 50, 20, "Maximum moves: ");
    replaceButton->hide();
    submitButton->callback(submitButtonCallback, this);
    addButton->callback(addingButtonCallback, this);
    replaceButton->callback(replaceButtonCallback, this);
    end();
    show();
}

LevelEditorWindow::LevelEditorWindow(std::string filename, Board board) : LevelEditorWindow() {
    replaceButton->show();
    filingName = filename;
    Canvas cv = convertObjectVectorToCanva(board.getBoard());
    setCanva(cv);
    draw();
    end();
    show();
}

Canvas LevelEditorWindow::convertObjectVectorToCanva(std::vector<std::vector<GameObject>> objectVector) {
    Canvas canvass = Canvas(objectVector[0].size(), objectVector.size());
    std::vector<std::vector<Cell>> c = canvass.getCells();
    int i = 0, j = 0;
    for (auto &line : objectVector) {
        j = 0;
        for (auto &elem : line) {
            if (elem.isEmpty()) {
                c[i][j].setCurrent(0);
            }else if (elem.isWall()) {
                c[i][j].setCurrent(1);
            }
            else if (elem.isBox()) {
                c[i][j].setCurrent(2);
            }
            else if (elem.isPlayer()) {
                c[i][j].setCurrent(3); 
            }
            else if (elem.isTarget()) {
                c[i][j].setCurrent(4);
            }
            else if (elem.isTp()) {
                c[i][j].setCurrent(5);
            }
            j++;
        }
        i++;
    }
    canvass.setCells(c);
    canvass.setNumberOfColumns(objectVector[0].size());
    canvass.setNumberOfLines(objectVector.size());
    return canvass;
}

void LevelEditorWindow::setCanva(Canvas canva){
    canvas = canva;
}

void LevelEditorWindow::displayLegend(){
    Rectangle player({STARTDISPLAYX, STARTDISPLAYY+260}, 20, 20, FL_BLACK, FL_GREEN);
    Text txtPlayer("Player", {STARTDISPLAYX+15, STARTDISPLAYY+270});
    Rectangle box({STARTDISPLAYX, STARTDISPLAYY+285}, 20, 20, FL_BLACK, FL_YELLOW);
    Text txtBox("Boxes", {STARTDISPLAYX+15, STARTDISPLAYY+295});
    Rectangle target({STARTDISPLAYX, STARTDISPLAYY+310}, 20, 20, FL_BLACK, FL_MAGENTA);
    Text txtTarget("Targets", {STARTDISPLAYX+15, STARTDISPLAYY+320});
    Rectangle tp({STARTDISPLAYX, STARTDISPLAYY+335}, 20, 20, FL_BLACK, FL_CYAN);
    Text txtTp("Tps", {STARTDISPLAYX+15, STARTDISPLAYY+345});
    Rectangle wall({STARTDISPLAYX, STARTDISPLAYY+360}, 20, 20, FL_BLACK, FL_BLUE);
    Text txtWall("Walls", {STARTDISPLAYX+15, STARTDISPLAYY+370});
    player.draw(); box.draw(); target.draw(); tp.draw(); wall.draw();
    txtPlayer.draw(); txtBox.draw(); txtTarget.draw(); txtTp.draw(); txtWall.draw();

}

void LevelEditorWindow::draw() {
    Fl_Window::draw();
    canvas.draw();
    displayLegend();
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
            else if (Fl::event_x() <= replaceButton->x()+replaceButton->w() and Fl::event_x() >=replaceButton->x() 
                        and Fl::event_y() <= replaceButton->y()+replaceButton->h() and Fl::event_y() >=replaceButton->y()) {
                replaceButton->do_callback();
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

void LevelEditorWindow::convertCanvaToTextFile(std::string fileName, bool addingAsNew) {
    std::string directory = "lvls/" + fileName + ".txt";

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
    if (addingAsNew) {
        std::ofstream allWrite("lvls/all.txt", std::ofstream::app);
        allWrite << fileName << "\n";
    }
    fl_alert("File added as : %s", fileName.c_str());
}

void LevelEditorWindow::replaceButtonCallback(Fl_Widget* w, void* ptr) {
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    if(me->isGridValid()) {
        int pos1 = me->filingName.find("/");
        std::string tmpStr = me->filingName.substr(pos1+1);
        int pos2 = tmpStr.find(".");
        std::string finalStr = tmpStr.substr(0, pos2);
        me->convertCanvaToTextFile(finalStr, false);
    }
}
    
void LevelEditorWindow::submitButtonCallback(Fl_Widget* w, void* ptr){
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    if ((atoi(me->lineInput->value()) > 2) and ((atoi(me->colInput->value()) > 2))) {
        Canvas newCanvas = Canvas(atoi(me->colInput->value()),atoi(me->lineInput->value()));
        newCanvas.setNumberOfColumns(atoi(me->colInput->value()));
        newCanvas.setNumberOfLines(atoi(me->lineInput->value()));
        me->setCanva(newCanvas);
        me->redraw();
    }
    else{
        fl_alert("You introduced bad dimensions, must be integers and greater than 2.");
    }
}

void LevelEditorWindow::addingButtonCallback(Fl_Widget* w, void* ptr){
    LevelEditorWindow* me = static_cast<LevelEditorWindow*>(ptr);
    if (me->isGridValid()) {
        me->convertCanvaToTextFile(me->getLastFileName(), true);
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

std::string LevelEditorWindow::getLastFileName() {
    std::ifstream allRead("lvls/all.txt");
    std::string line;
    int counter = 0;
    while(std::getline(allRead, line)) {
        counter++;
    }
    
    std::string fname = "lvl" + std::to_string(counter+1);

    return fname;
}
