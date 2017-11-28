#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "GameBoard.h"
#include "preset.h"
#include "util.h"

using namespace std;
using SPuzzle::Game;
using SPuzzle::Direction;

Fl_Group* splash;
Fl_Group* game_win;
Fl_Group* game_pause;
Fl_Group* about_win;
Fl_Group* difficulty;

Fl_Window *win;
GameBoard *gb;
GameBoard *demo;
InfoBoard *ib;

const vector<Direction> demo_steps = {
    SPuzzle::RIGHT,
    SPuzzle::DOWN,
    SPuzzle::LEFT,
    SPuzzle::UP,
    SPuzzle::UP,
    SPuzzle::UP,
};
vector<Direction> demo_remain = demo_steps;



Fl_PNG_Image* img_splash =     new Fl_PNG_Image("res/splash.png");
Fl_PNG_Image* img_difficulty = new Fl_PNG_Image("res/difficulty.png");
Fl_PNG_Image* img_demo =       new Fl_PNG_Image("res/demo.png");
Fl_PNG_Image* img_game_bg =    new Fl_PNG_Image("res/game.png");
Fl_PNG_Image* img_powered_by = new Fl_PNG_Image("res/powered_by.png");
Fl_PNG_Image* img_game =       new Fl_PNG_Image("res/games/default.png");

Fl_Button* pause;

Game* game;
Game* demo_game;
ConfigParser* config;

static void hideall();
static void force_quit(Fl_Widget* btn = nullptr, void* = nullptr);
