#include "GameBoard.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv) {
    Fl_Window *win = new Fl_Window(0,0,800,600,"FL");
    GameBoard *gb = new GameBoard(100,100,400,400);

    win->end();
    win->show(argc, argv);
    return Fl::run();
}
