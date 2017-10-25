#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>

#include "game.h"

#pragma once

using SPuzzle::Game;

class GameBoard : public Fl_Box {
public:
    Game* game;   // The game the board represents
    GameBoard(int x, int y, int w, int h, SPuzzle::Game* game)
        : Fl_Box(x, y, w, h, NULL), game(game) {}

    // Override the draw function and event handle function
    void draw();
    int handle(int event);
};


class InfoBoard : public Fl_Box {
public:
    Game* game;   // The game the board represents
    InfoBoard(int x, int y, int w, int h, SPuzzle::Game* game)
        : Fl_Box(x, y, w, h, NULL), game(game) {}

    // Override the draw function and event handle function
    void draw();
};
