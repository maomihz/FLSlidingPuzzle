#include "GameBoard.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

Fl_Window *win;
GameBoard *gb;


// void new_game(Fl_Widget* w, void* args) {
//     gb->game.new_game();
// }

int main(int argc, char **argv) {
    win = new Fl_Window(0,0,800,600,"FL");
    gb = new GameBoard(100,100,800,400);
    // step = new Fl_Box(600,200,100,50,"bz");



    win->end();
    win->show(argc, argv);
    while (Fl::check()) {
        // Fl::redraw();
    }
}
