
#include "mainWindow.hpp"

int main(int argc, char *argv[]) {
    srand(time(0));
    MainWindow window;
    window.show(argc, argv);
    return Fl::run();
}


