#ifndef _EDITOR_HPP
#define _EDITOR_HPP


#include <FL/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/fl_types.h>
#include <FL/Fl_Input.H>
#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>
#include <Fl/Fl_Choice.H>
#include <memory.h>

class LevelEditorWindow : public Fl_Window {
 public:
     LevelEditorWindow() : Fl_Window(000, 000, 1000, 975, "Level Editor") {
         std::cout << "Welcome" << std::endl;
     }
};

void generateButtonEditor();
#endif
