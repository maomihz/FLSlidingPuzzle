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

    // Animation variables. These are used to track the move animation
    Point anim_start; // The point the animation starts
    Point anim_end;   // The point the animation ends
    double anim_run;  // The percentage of animation progress. Value 0 ~ 1.

    // Points to the tile that the mouse is currently over. Used to draw
    // boarder.
    Point hover;
    // Points to the hint. It is only used for drawing border.
    Point hint;

    // A "Read Only" board does not react to any events and does not draw
    // any border. Used for demonstration purpose.
    bool readonly_;


    GameBoard(int x, int y, int w, int h, SPuzzle::Game* game, Fl_Image* image)
        : Fl_Box(x, y, w, h, NULL),  // We don't need label here
        game(game), image(image),
        anim_start(0,0), anim_end(0,0), anim_run(-1),
        hover{-1,-1}, hint{-1,-1},  // These invalid points would not draw
        readonly_(false) {}

    // Override the draw function and event handle function
    void draw();
    int handle(int event);

    // Animated move function, which differs from the move function in the Game
    // class. Supports both keyboard and mouse action
    void move(SPuzzle::Direction dir);
    void click(Point p);

    // Set the read only value.
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
    ConfigParser* config; // The global configuration,
                          // used to display high score
    InfoBoard(int x, int y, int w, int h, SPuzzle::Game* game, ConfigParser* config)
        : Fl_Box(x, y, w, h, NULL),
        game(game),
        config(config) {}

    // Override the draw function and event handle function
    void draw();
};
