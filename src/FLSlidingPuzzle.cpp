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



Fl_PNG_Image* png = new Fl_PNG_Image("splash.png");
Fl_PNG_Image* png2 = new Fl_PNG_Image("bbb.png");
Fl_PNG_Image* small = new Fl_PNG_Image("small.png");
Fl_PNG_Image* powered_by = new Fl_PNG_Image("powered_by.png");
Fl_PNG_Image* bg = new Fl_PNG_Image("bg.png");



Game* game;
Game* demo_game;
ConfigParser* config;

static void hideall();


static void update_count(void*) {
    ib->redraw();
    Fl::repeat_timeout(0.05, update_count);
}

static void show_game(Fl_Widget* btn, void* data) {
    // Before showing the game, ask the user for name
    // If the name is already set then read that otherwise
    // set to default "Player"
    string player_name;
    try {
        player_name = config->get("player.name");
    } catch (out_of_range e) {
        player_name = "Player";
    }

    // Show the input dialog
    const char* name = fl_input("What is your name?", player_name.c_str());
    if (!name) return;  // If the user clicked cancel, then fail
    if (!strlen(name)) return; // If the user enter empty string then return
    config->set("player.name", name, true);
    hideall();

    // If the user does not input a name then abort
    int mode = fl_intptr_t(data);
    switch (mode) {
    case 1:
        game->new_game(EASY.at(rand() % EASY.size()), 10, "easy");
        break;
    case 2:
        game->new_game(NORMAL.at(rand() % NORMAL.size()), 20, "normal");
        break;
    case 3:
        game->new_game(HARD.at(rand() % HARD.size()), 40, "hard");
        break;
    case 4:
        game->new_game(IMPOSSIBLE.at(rand() % IMPOSSIBLE.size()), 80, "impossible");
        break;
    default:
        game->new_game("random");
        break;
    }
    game_win->show();
    Fl::add_timeout(0.5, update_count);
}

static void show_difficulty(Fl_Widget* btn, void*) {
    hideall();
    difficulty->show();
}

static void show_about(Fl_Widget* btn, void*) {
    hideall();
    about_win->show();
}


static void anim_demo(void* data) {
    if (demo_remain.size() > 0) {
        demo->move(demo_remain.front());
        demo_remain.erase(demo_remain.begin());
    } else {
        demo_game->new_game(DEMO, -1, "demo");
        demo_remain = demo_steps;
        demo->redraw();
    }
    if (demo_remain.size() > 0) {
        Fl::repeat_timeout(1, anim_demo);
    } else {
        Fl::repeat_timeout(3, anim_demo);
    }

}

static void show_main(Fl_Widget* btn, void*) {
    hideall();
    demo_game->new_game(DEMO, -1, "demo");
    demo_remain = demo_steps;
    Fl::add_timeout(1, anim_demo);
    splash->show();
}

static void game_end(Fl_Widget* gboard, void*) {
    ib->redraw();
    Fl::remove_timeout(update_count);
    int score = game->score();
    string player = config->get("player.name");
    vector<int> scores = config->get_v(game->description() + ".scores");
    vector<string> players = config->get_v_str(game->description() + ".players");
    magic_insert(score, player, scores, players);
    config->set(game->description() + ".scores", scores);
    config->set(game->description() + ".players", players);
    config->write();


    if (game->win()) {
        fl_alert("You Win!");
    } else {
        fl_alert("Game Over!");
    }
    switch(fl_choice("Do you want to play another game?", "No", "Yes", 0)) {
        case 0: // No
            exit(0);
        case 1: // Yes
            show_difficulty(nullptr, nullptr);
    }
}

static void anim_hint(void* data) {
    int d = fl_intptr_t(data);
    if (d >= 0) {
        if (d & 1) {
            gb->hint = game->get_move(game->hint());
        } else {
            gb->hint.x = -1;
        }
        gb->redraw();
        Fl::repeat_timeout(0.1, anim_hint, (void*)(intptr_t)(d - 1));
    }
}

static void get_hint(Fl_Widget* btn, void*) {
    Fl::add_timeout(0.01, anim_hint, (void*)6);
}


static void hideall() {
    for (int i = 0; i < win->children(); ++i) {
        win->child(i)->hide();
    }
    Fl::remove_timeout(anim_demo);
}

int main(int argc, char **argv) {
    // Seed random number generator
    srand(time(NULL));

    // Initialize configurations
    config = new ConfigParser("leaderboard.conf");
    config->load();
    vector<int> easy_scores(5,0),
                normal_scores(5,0),
                hard_scores(5,0),
                impossible_scores(5,0),
                random_scores(5,0);
    vector<string> easy_players(5,""),
                normal_players(5,""),
                hard_players(5,""),
                impossible_players(5,""),
                random_players(5,"");

    config->set("easy.scores", easy_scores, true);
    config->set("normal.scores", normal_scores, true);
    config->set("hard.scores", hard_scores, true);
    config->set("impossible.scores", impossible_scores, true);
    config->set("random.scores", random_scores, true);

    config->set("easy.players", easy_players, true);
    config->set("normal.players", normal_players, true);
    config->set("hard.players", hard_players, true);
    config->set("impossible.players", impossible_players, true);
    config->set("random.players", random_players, true);

    // Create the FL Window
    string title = "FL Sliding Puzzle";
    win = new Fl_Window(100, 100, 800, 600, title.c_str());
    win->position((Fl::w() - win->w())/2, (Fl::h() - win->h())/2);


    // *** Splash Screen ***
    splash            = new Fl_Group(0,0,win->w(), win->h());
    Fl_Box* main_bg   = new Fl_Box(0,0,win->w(), win->h());
    main_bg->image(png);
    Fl_Button* start  = new Fl_Button(150,450,100,50,"New Game");
    Fl_Button* help   = new Fl_Button(350,450,100,50,"Help");
    Fl_Button* about  = new Fl_Button(550,450,100,50,"About");
    demo_game = new Game(4);
    demo_game->new_game(DEMO, -1, "demo");
    demo = new GameBoard(600,100,150,150, demo_game, small);
    demo->readonly(true);
    Fl::add_timeout(1, anim_demo);
    start->callback(show_difficulty);
    about->callback(show_about);
    splash->end();


    // *** Difficulty Selection ***
    difficulty            = new Fl_Group(0,0,win->w(),win->h());
    Fl_Box* difficulty_bg = new Fl_Box(0,0,win->w(), win->h());
    difficulty_bg->image(png);
    Fl_Button* easy       = new Fl_Button(150,450,100,50,"Easy");
    Fl_Button* normal     = new Fl_Button(250,450,100,50,"Normal");
    Fl_Button* hard       = new Fl_Button(350,450,100,50,"Hard");
    Fl_Button* impossible = new Fl_Button(450,450,100,50,"Impossible");
    Fl_Button* random     = new Fl_Button(550,450,100,50,"Random");
    Fl_Button* back       = new Fl_Button(350,500,100,50,"Go Back");
    easy      ->callback(show_game, (void*)1);
    normal    ->callback(show_game, (void*)2);
    hard      ->callback(show_game, (void*)3);
    impossible->callback(show_game, (void*)4);
    random    ->callback(show_game, (void*)0);
    back      ->callback(show_main);
    difficulty->end();
    difficulty->hide();


    // *** Game ***
    game_win = new Fl_Group(0,0,win->w(), win->h());
    game = new Game(4);
    Fl_Box* bgimg = new Fl_Box(0,0,win->w(),win->h());
    bgimg->image(bg);
    gb = new GameBoard(100,100,400,400, game, png2);
    ib = new InfoBoard(530,200,260,300, game, config);
    gb->callback(game_end);
    Fl_Button* pause = new Fl_Button(550, 50, 100, 50, "Pause");
    Fl_Button* hint =  new Fl_Button(650, 50, 100, 50, "Hint");
    hint->callback(get_hint);
    game_win->end();
    game_win->hide();


    // *** About ***
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
