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
    gb = new GameBoard(100,100,800,400, 4);



    win->end();
    win->show(argc, argv);
    while (Fl::check()) {
    }
}
