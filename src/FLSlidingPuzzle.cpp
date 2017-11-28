#include "FLSlidingPuzzle.h"

static void update_count(void*) {
    ib->redraw();
    Fl::repeat_timeout(0.05, update_count);
}

static void show_game(Fl_Widget* btn = nullptr, void* data = nullptr) {
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

    // Update the picture
    gb->image = img_games.at(selected_img_game).first;
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
    pause->label("Quit");
    game_win->show();
    Fl::add_timeout(0.5, update_count);
}

static void show_difficulty(Fl_Widget* btn = nullptr, void* = nullptr) {
    hideall();
    difficulty->show();
}

static void show_about(Fl_Widget* btn = nullptr, void* = nullptr) {
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

static void show_main(Fl_Widget* btn = nullptr, void* = nullptr) {
    hideall();
    demo_game->new_game(DEMO, -1, "demo");
    demo_remain = demo_steps;
    Fl::add_timeout(1, anim_demo);
    splash->show();
}

static void show_settings(Fl_Widget* btn = nullptr, void* = nullptr) {
    hideall();
    settings_win->show();
}

static void game_end(Fl_Widget* gboard, void*) {
    // if neither win or lose, then the game is started.
    if (!game->win() && !game->lose()) {
        pause->label("Pause");
        return;
    }
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

static void toggle_pause(Fl_Widget* btn = nullptr, void* = nullptr) {
    // cout << game->paused() << endl;
    if (game->started()) {
        if (game->paused()) {
            game->resume();
            pause->label("Pause");
            game_pause->hide();
        } else {
            game->pause();
            pause->label("Resume");
            game_pause->show();
        }
    } else {
        show_main();
    }
    gb->redraw();
    gb->take_focus();
}

static void select_img(Fl_Widget* btn, void* v) {
    int which = fl_intptr_t(v);
    selected_img_game += which;
    if (selected_img_game < 0) {
        selected_img_game = 0;
    } else if (selected_img_game >= (int)img_games.size()) {
        selected_img_game = img_games.size() - 1;
    }

    // Update the settings image display
    selection_box->image(img_games.at(selected_img_game).first);
    selection_box->label((img_games.at(selected_img_game).second).c_str());

    // Update the configuration
    config->set("selected_img", selected_img_game);
    config->write();
    Fl::redraw();

}

static void force_quit(Fl_Widget* btn, void*) {
    switch(fl_choice("Do you want to give up and quit?", "No", "Yes", 0)) {
        case 1:
            show_main();
    }
}

static void cb_exit(Fl_Widget* btn, void*) {
    exit(0);
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

    // Initialize default configurations
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

    config->set("selected_img", 0, true);

    selected_img_game = config->get_int("selected_img");

    // Create the FL Window
    string title = "FL Sliding Puzzle";
    win = new Fl_Window(100, 100, 800, 600, title.c_str());
    win->position((Fl::w() - win->w())/2, (Fl::h() - win->h())/2);


    // *** Splash Screen ***
    splash            = new Fl_Group(0,0,win->w(), win->h());
    Fl_Box* main_bg   = new Fl_Box(0,0,win->w(), win->h());
    main_bg->image(img_splash);
    Fl_Button* start    = new Fl_Button(200,450,100,50,"New Game");
    Fl_Button* help     = new Fl_Button(350,450,100,50,"Help");
    Fl_Button* about    = new Fl_Button(500,450,100,50,"About");
    Fl_Button* settings = new Fl_Button(280,525,100,50,"Settings");
    Fl_Button* quit     = new Fl_Button(420,525,100,50,"Exit");
    demo_game = new Game(4);
    demo_game->new_game(DEMO, -1, "demo");
    demo = new GameBoard(600,100,150,150, demo_game, img_demo);
    demo->readonly(true);
    Fl::add_timeout(1, anim_demo);
    start->callback(show_difficulty);
    about->callback(show_about);
    settings->callback(show_settings);
    quit->callback(cb_exit);
    splash->end();


    // *** Difficulty Selection ***
    difficulty            = new Fl_Group(0,0,win->w(),win->h());
    Fl_Box* difficulty_bg = new Fl_Box(0,0,win->w(), win->h());
    difficulty_bg->image(img_difficulty);
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
    // Overall background image
    Fl_Box* bgimg = new Fl_Box(0,0,win->w(),win->h());
    bgimg->image(img_game_bg);
    gb = new GameBoard(100,100,400,400, game, img_games.at(selected_img_game).first);
    ib = new InfoBoard(530,200,260,300, game, config);
    gb->callback(game_end);
    pause = new Fl_Button(550, 50, 100, 50, "Quit");
    pause->callback(toggle_pause);
    Fl_Button* hint =  new Fl_Button(650, 50, 100, 50, "Hint");
    hint->callback(get_hint);
    game_win->end();
    game_win->hide();


    // *** Game Pause ***
    game_pause = new Fl_Group(0,0,win->w(), win->h());
    Fl_Button* back_main = new Fl_Button(600, 100, 100, 50, "Back to Main");
    back_main->callback(force_quit);
    Fl_Box* pause_label = new Fl_Box(100, 0, 400, 50, "Game Paused");
    pause_label->align(FL_ALIGN_CENTER);
    pause_label->labelsize(40);
    game_pause->end();
    game_pause->hide();



    // *** About ***
    about_win = new Fl_Group(0,0,win->w(), win->h());
    Fl_Box *about_box    = new Fl_Box(100,100,100,100, "");
    Fl_Button *main_btn  = new Fl_Button(350,500,100,50,"Go back");
    about_box->image(img_powered_by);
    about_box->position((win->w() - about_box->w()) / 2, 200);
    main_btn->callback(show_main);
    about_win->end();
    about_win->hide();

    // *** Settings ***
    settings_win = new Fl_Group(0,0,win->w(), win->h());
    Fl_Box* settings_bg = new Fl_Box(0,0,win->w(), win->h());
    settings_bg->image(img_settings);
    selection_box = new Fl_Box(50,50,400,400);
    selection_box->labelsize(20);
    select_img(nullptr, (void*)0);
    Fl_Button *prev_img = new Fl_Button(100,500,100,50,"Previous");
    Fl_Button *next_img = new Fl_Button(300,500,100,50,"Next");
    prev_img->callback(select_img, (void*)-1);
    next_img->callback(select_img, (void*)1);
    Fl_Button *save = new Fl_Button(500,500,100,50,"Save");
    save->callback(show_main);
    settings_win->end();
    settings_win->hide();

    win->end();
    win->show(argc, argv);
    return Fl::run();
}
