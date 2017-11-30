#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <utility>

#include "GameBoard.h"
#include "InfoBoard.h"
#include "HelpPanel.h"
#include "preset.h"
#include "util.h"
#include "configparser.h"

using namespace std;
using SPuzzle::Game;
using SPuzzle::Direction;

Fl_Group* splash;
Fl_Group* game_win;
Fl_Group* game_pause;
Fl_Group* about_win;
Fl_Group* difficulty;
Fl_Group* settings_win;
Fl_Group* help_win;

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
Fl_PNG_Image* img_leaderboard= new Fl_PNG_Image("res/leaderboard_bg.png");
Fl_PNG_Image* img_powered_by = new Fl_PNG_Image("res/powered_by.png");
Fl_PNG_Image* img_settings =   new Fl_PNG_Image("res/settings_bg.png");
vector<pair<Fl_Image*, string>> img_games = {
    pair<Fl_JPEG_Image*, string>(new Fl_JPEG_Image("res/games/default.jpg"), "Numbers"),
    pair<Fl_JPEG_Image*, string>(new Fl_JPEG_Image("res/games/puppy.jpg"), "Puppy"),
    pair<Fl_JPEG_Image*, string>(new Fl_JPEG_Image("res/games/deemo.jpg"), "Alice"),
    pair<Fl_JPEG_Image*, string>(new Fl_JPEG_Image("res/games/miku.jpg"), "Hatsume Miku")
};
vector<Fl_Image*> img_help = {
    new Fl_PNG_Image("res/help/1.png"),
    new Fl_PNG_Image("res/help/2.png"),
    new Fl_PNG_Image("res/help/3.png"),
};

Fl_Button* pause;

Game* game;
Game* demo_game;

int selected_img_game = 0;
Fl_Box *selection_box;

ConfigParser* config;

static void hideall();
static void force_quit(Fl_Widget* btn = nullptr, void* = nullptr);
