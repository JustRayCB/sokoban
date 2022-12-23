#include "levelEditor.hpp"
#include <cstring>

void generateButtonEditor(){
    Fl_Window* editor = new Fl_Window (000,000,1000,975,"Editor");
    Fl_Input* colInput = new Fl_Input (150, 10, 50, 20, "Number of columns: ");
    Fl_Input* lineInput = new Fl_Input (150, 30, 50, 20, "Number of lines: ");
    editor->show();
    colInput->show();
    lineInput->show();

    if (not strcmp(colInput->value(), "") and not strcmp(lineInput->value(), "")) {
        std::cout << "HIIII" << std::endl;
    }
}
