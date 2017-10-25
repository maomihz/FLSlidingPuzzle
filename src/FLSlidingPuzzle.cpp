#include "GameBoard.h"
#include "InfoBoard.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
using SPuzzle::Game;

Fl_Window *win;
GameBoard *gb;
InfoBoard *ib;

Game *game;

void update_count(void*) {
    ib->redraw();
    Fl::add_timeout(0.05, update_count);
}

int main(int argc, char **argv) {
    // Create the FL Window
    string title = "FL Sliding Puzzle";
    win = new Fl_Window(100, 100, 800, 600, title.c_str());
    win->position((Fl::w() - win->w())/2, (Fl::h() - win->h())/2);

    // Start a new game
    game = new Game(4);
    gb = new GameBoard(100,100,400,400, game);
    ib = new InfoBoard(600,200,100,300, game);

    Fl::add_timeout(0.5, update_count);


    win->end();
    win->show(argc, argv);
    return Fl::run();
}
