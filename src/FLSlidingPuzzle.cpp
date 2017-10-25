#include "GameBoard.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;
using SPuzzle::Game;

Fl_Window *win;
GameBoard *gb;

Game *game;

int main(int argc, char **argv) {
    // Create the FL Window
    string title = "FL Sliding Puzzle";
    win = new Fl_Window(100, 100, 800, 600, title.c_str());
    win->position((Fl::w() - win->w())/2, (Fl::h() - win->h())/2);

    // Start a new game
    game = new Game(4);
    gb = new GameBoard(100,100,800,400, game);



    win->end();
    win->show(argc, argv);
    while (Fl::check()) {
    }
}
