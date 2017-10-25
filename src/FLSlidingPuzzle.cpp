#include "GameBoard.h"
#include "FL/Fl_Button.H"
#include "FL/Fl_PNG_Image.H"
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

void add_game(Fl_Widget* btn, void*) {
    game = new Game(4);
    gb = new GameBoard(100,100,400,400, game);
    ib = new InfoBoard(600,200,100,300, game);
    win->clear();
    win->add(gb);
    win->add(ib);
    win->focus(gb);
    win->redraw();
    Fl::add_timeout(0.5, update_count);
}

int main(int argc, char **argv) {
    // Create the FL Window
    string title = "FL Sliding Puzzle";
    win = new Fl_Window(100, 100, 800, 600, title.c_str());
    win->position((Fl::w() - win->w())/2, (Fl::h() - win->h())/2);

    Fl_Box* img = new Fl_Box(0,0,win->w(), win->h());
    Fl_PNG_Image png("splash.png");
    img->image(png);

    Fl_Button* start = new Fl_Button(150,450,100,50,"New Game");
    Fl_Button* help = new Fl_Button(350,450,100,50,"Help");
    Fl_Button* about = new Fl_Button(550,450,100,50,"About");
    start->callback(add_game);


    win->end();
    win->show(argc, argv);
    return Fl::run();
}
