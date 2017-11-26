#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>

#include "game.h"
#include "configparser.h"

#pragma once
using SPuzzle::Game;
using SPuzzle::Point;


// The GameBoard class is used to represent an actual game board. The internal
// game board does not handle any images, but this class splits and paint the
// image to the screen. It refreshes only when an event happens. When the game
// is started, the focus must be on this Gameboard otherwise event would not
// be handled.
class GameBoard : public Fl_Box {
public:
    Game* game;        // The game the board represents
    Fl_Image* image;   // The image that is displayed on screen

    Point anim_start;
    Point anim_end;
    double anim_run;
    Point hover;
    Point hint;

    bool readonly_;


    GameBoard(int x, int y, int w, int h, SPuzzle::Game* game, Fl_Image* image)
        : Fl_Box(x, y, w, h, NULL),  // We don't need label here
        game(game),
        image(image),
        anim_start(0,0),
        anim_end(0,0),
        anim_run(-1),
        hover{-1,-1},
        hint{-1,-1},
        readonly_(false) {}

    // Override the draw function and event handle function
    void draw();
    int handle(int event);
    void move(SPuzzle::Direction dir);
    void click(Point p);
    void readonly(bool value = true) {
        readonly_ = value;
    }
};


// The InfoBoard class is used to display information about the game and is
// seperated from the main board. Information include the duration, number of
// steps, and the score. When created, the same pointer of a Game object as the
// GameBoard must be passed in in order to access the data correctly.
class InfoBoard : public Fl_Box {
public:
    Game* game;   // The game the board represents
    ConfigParser* config; // The configuration, used to display high score
    InfoBoard(int x, int y, int w, int h, SPuzzle::Game* game, ConfigParser* config)
        : Fl_Box(x, y, w, h, NULL),
        game(game),
        config(config) {}

    // Override the draw function and event handle function
    void draw();
};
