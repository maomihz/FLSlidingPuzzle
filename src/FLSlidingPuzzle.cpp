#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "GameBoard.h"
#include "preset.h"

using namespace std;
using SPuzzle::Game;

Fl_Group* splash;
Fl_Group* game_win;
Fl_Group* about_win;
Fl_Group* difficulty;

Fl_Window *win;
GameBoard *gb;
InfoBoard *ib;


Fl_PNG_Image* png = new Fl_PNG_Image("splash.png");
Fl_PNG_Image* png2 = new Fl_PNG_Image("bbb.png");
Fl_PNG_Image* powered_by = new Fl_PNG_Image("powered_by.png");
Fl_PNG_Image* bg = new Fl_PNG_Image("bg.png");



Game *game;


static void update_count(void*) {
    ib->redraw();
    Fl::repeat_timeout(0.05, update_count);
}

static void show_game(Fl_Widget* btn, void*) {
    for (int i = 0; i < win->children(); ++i) {
        win->child(i)->hide();
    }
    game_win->show();
    Fl::add_timeout(0.5, update_count);
}

static void show_difficulty(Fl_Widget* btn, void*) {
    for (int i = 0; i < win->children(); ++i) {
        win->child(i)->hide();
    }
    difficulty->show();
}

void show_about(Fl_Widget* btn, void*) {
    for (int i = 0; i < win->children(); ++i) {
        win->child(i)->hide();
    }
    about_win->show();
}

static void show_main(Fl_Widget* btn, void*) {
    for (int i = 0; i < win->children(); ++i) {
        win->child(i)->hide();
    }
    splash->show();
}

int main(int argc, char **argv) {
    // Create the FL Window
    string title = "FL Sliding Puzzle";
    win = new Fl_Window(100, 100, 800, 600, title.c_str());
    win->position((Fl::w() - win->w())/2, (Fl::h() - win->h())/2);

    splash            = new Fl_Group(0,0,win->w(), win->h());
    Fl_Box* main_bg   = new Fl_Box(0,0,win->w(), win->h());
    main_bg->image(png);
    Fl_Button* start  = new Fl_Button(150,450,100,50,"New Game");
    Fl_Button* help   = new Fl_Button(350,450,100,50,"Help");
    Fl_Button* about  = new Fl_Button(550,450,100,50,"About");
    start->callback(show_difficulty);
    about->callback(show_about);
    splash->end();


    difficulty            = new Fl_Group(0,0,win->w(),win->h());
    Fl_Box* difficulty_bg = new Fl_Box(0,0,win->w(), win->h());
    difficulty_bg->image(png);
    Fl_Button* easy       = new Fl_Button(150,450,100,50,"Easy");
    Fl_Button* normal     = new Fl_Button(250,450,100,50,"Normal");
    Fl_Button* hard       = new Fl_Button(350,450,100,50,"Hard");
    Fl_Button* impossible = new Fl_Button(450,450,100,50,"Impossible");
    Fl_Button* random     = new Fl_Button(550,450,100,50,"Random");
    Fl_Button* back       = new Fl_Button(350,500,100,50,"Go Back");
    random->callback(show_game);
    back->callback(show_main);
    difficulty->end();
    difficulty->hide();



    game_win = new Fl_Group(0,0,win->w(), win->h());
    game = new Game(4);
    game->new_game();
    Fl_Box* bgimg = new Fl_Box(0,0,win->w(),win->h());
    bgimg->image(bg);
    gb = new GameBoard(100,100,400,400, game, png2);
    ib = new InfoBoard(600,200,100,300, game);
    game_win->end();
    game_win->hide();


    about_win = new Fl_Group(0,0,win->w(), win->h());
    Fl_Box *about_box    = new Fl_Box(100,100,100,100, "Placeholder Test");
    Fl_Button *main_btn  = new Fl_Button(350,500,100,50,"Go back");

    about_box->image(powered_by);
    about_box->position((win->w() - about_box->w()) / 2, 200);
    main_btn->callback(show_main);
    about_win->end();
    about_win->hide();


    win->end();
    win->show(argc, argv);
    return Fl::run();
}
