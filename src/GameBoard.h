#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>

#include "game.h"

#pragma once

class GameBoard : public Fl_Box {
public:
    SPuzzle::Game* game;   // The game the board represents
    GameBoard(int x, int y, int w, int h, SPuzzle::Game* game)
        : Fl_Box(x, y, w, h, NULL), game(game) {}

    // Override the draw function and event handle function
    void draw();
    int handle(int event);
};
