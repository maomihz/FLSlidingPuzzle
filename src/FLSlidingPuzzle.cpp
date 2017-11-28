#include "FLSlidingPuzzle.h"

// Update the info board, which is used to display time, steps and leaderboard.
// Callback for a timeout
static void update_count(void*) {
    ib->redraw();
    Fl::repeat_timeout(0.05, update_count);
}

// Start a new game and show the game window. Callback for the start button.
// Takes a data to specify the type of the game, and in this program there
// are 5 types, easy normal hard impossible and random.
static void show_game(Fl_Widget* btn = nullptr, void* data = nullptr) {
    // Before showing the game, ask the user for name
    // If the name is already set then read that otherwise
    // set to default "Player"
    string player_name;
    try {
        player_name = config->get<string>("player.name");
    } catch (out_of_range e) {
        player_name = "Player";
    }

    // Show the input dialog
    const char* name = fl_input("What is your name?", player_name.c_str());
    if (!name) return;  // If the user clicked cancel, then fail
    if (!strlen(name)) return; // If the user enter empty string then return
    config->set("player.name", name, true); // Set the configuration item

    // Update the picture according to configuration
    gb->image = img_games.at(selected_img_game).first;

    hideall();

    // There are two different game modes, the puzzle mode which limits the
    // amount of steps, and the free mode which is generated randomly.
    // They have different scoring system.
    int mode = fl_intptr_t(data);
    switch (mode) {
    case 1: // Integer 1 represents "Easy"
        game->new_game(EASY.at(rand() % EASY.size()), 10, "easy");
        break;
    case 2: // Integer 2 represents "Normal"
        game->new_game(NORMAL.at(rand() % NORMAL.size()), 20, "normal");
        break;
    case 3: // Integer 3 represents "Hard"
        game->new_game(HARD.at(rand() % HARD.size()), 40, "hard");
        break;
    case 4: // Integer 4 represents "Impossible"
        game->new_game(IMPOSSIBLE.at(rand() % IMPOSSIBLE.size()), 80, "impossible");
        break;
    default: // Integer 0 (usually) represents "Random"
        game->new_game("random");
        break;
    }

    // When a new game starts, the "Pause" button should not work, so it is
    // changed to Quit, which exits to the main menu without confirmation.
    pause->label("Quit");

    // Show the game window
    game_win->show();

    // Set a timeout to update the info board
    Fl::add_timeout(0.5, update_count);

    // Refresh Leaderboard, take in newly inserted score
    ib->update();
}

// Show the difficulty selection screen. Very simple callback, just hides
// all other elements and show the difficulty group.
static void show_difficulty(Fl_Widget* btn = nullptr, void* = nullptr) {
    hideall();
    difficulty->show();
}

// Show the about screen. Simple callback.
static void show_about(Fl_Widget* btn = nullptr, void* = nullptr) {
    hideall();
    about_win->show();
}


// Callback to control the demo animation on the splash screen.
static void anim_demo(void* data) {
    // If the demo game is not completed yet, try to take a pre-defined
    // move.
    if (demo_remain.size() > 0) {
        demo->move(demo_remain.front());
        demo_remain.erase(demo_remain.begin());
    // If the demo game is already completed, then reset the game to original
    // layout, and start the demo again.
    } else {
        // Reset the game and reset the pre-defined steps
        demo_game->new_game(DEMO, -1, "demo");
        demo_remain = demo_steps;

        // Redraw the demo board since the data is changed but the the GUI is
        // not notified
        demo->redraw();
    }
    // After the movement is made, if the game is still not completed, then
    // wait for 1 second and take the next move.
    if (demo_remain.size() > 0) {
        Fl::repeat_timeout(1, anim_demo);
    // Otherwise wait for 3 seconds before the game get resetted
    } else {
        Fl::repeat_timeout(3, anim_demo);
    }

}

// Show the splash screen. Simple callback.
static void show_main(Fl_Widget* btn = nullptr, void* = nullptr) {
    hideall();

    // Reset the demo game no matter what. Wait for 1 second and take a move
    demo_game->new_game(DEMO, -1, "demo");
    demo_remain = demo_steps;
    Fl::add_timeout(1, anim_demo);

    splash->show();
}

// Show the setting screen. Simple callback.
static void show_settings(Fl_Widget* btn = nullptr, void* = nullptr) {
    hideall();
    settings_win->show();
}

// Callback for both the end of the game and the start of the game.
// Update some elements when (after) the game is started, and prompt the user
// when the game is ended.
static void game_end(Fl_Widget* gboard, void*) {
    // Handle the start of the game.
    // if neither win or lose, then the game is started.
    if (!game->win() && !game->lose()) {
        pause->label("Pause");
        return;
    }


    // Handle the end of the game
    // First stop updating the score (info) board
    ib->redraw();
    Fl::remove_timeout(update_count);

    // Insert the current score to the list of scores, and write back to the
    // file
    int score = game->score();
    string player = config->get<string>("player.name");
    vector<int> scores
        = config->get<vector<int>>(game->description() + ".scores");
    vector<string> players
        = config->get<vector<string>>(game->description() + ".players");
    magic_insert(score, player, scores, players); // Insert the score
    config->set(game->description() + ".scores", scores);
    config->set(game->description() + ".players", players);
    config->write();

    // Display a dialog to indicate win or lose
    if (game->win()) {
        fl_alert("You Win! Your score is %d.", score);
    } else {
        fl_alert("Game Over! Your score is %d.", score);
    }

    // Ask the user whether start another game or quit
    switch(fl_choice("Do you want to play another game?", "No", "Yes", 0)) {
        case 0: // No
            exit(0);
        case 1: // Yes
            show_difficulty(nullptr, nullptr);
    }
}


// Show the hint "blinking" animation. The integer data indicates number of
// blinks remain.
static void anim_hint(void* data) {
    int d = fl_intptr_t(data);
    if (d >= 0) {
        // If the number of blinks is odd, then show the boarder
        if (d & 1) {
            gb->hint = game->get_move(game->hint());
        // Otherwise hide the boarder
        } else {
            // Make the hint point invalid to hide
            gb->hint.x = -1;
        }

        // Redraw the game board
        gb->redraw();
        Fl::repeat_timeout(0.1, anim_hint, (void*)(intptr_t)(d - 1));
    }
}


// Callback function to start the blinking hint
static void get_hint(Fl_Widget* btn = nullptr, void* = nullptr) {
    Fl::add_timeout(0.01, anim_hint, (void*)6);
}


// callback function to toggle the pause state of the game
static void toggle_pause(Fl_Widget* btn = nullptr, void* = nullptr) {
    // If the game is already started, then the button actually performs
    // the "pause" function
    if (game->started()) {
        // If the game is paused, then resume the game
        if (game->paused()) {
            game->resume();
            pause->label("Pause"); // Update the label
            game_pause->hide();    // hide the pause menu
        // Otherwise pause the game
        } else {
            game->pause();
            pause->label("Resume");
            game_pause->show();
        }
    // If the game is not yet started, then the button performs "Quit"
    // function. The label of the button is updated elsewhere.
    } else {
        // Quit to the main menu (splash screen)
        show_main();
    }
    // Redraw the game board to keep it updated. Make the game board take
    // focus so that it can receive keyboard inputs.
    gb->redraw();
    gb->take_focus();
}

// Callback function for the settings screen to switch selected images.
// the integer argument is either +1 or -1, indicating select the next
// image or previous image.
// the "selected image" is used for the gameplay.
static void select_img(Fl_Widget* btn, void* v) {
    int which = fl_intptr_t(v);
    selected_img_game += which;

    // Prevent the index exceed boundary
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

    // Redraw all the windows to update the display
    Fl::redraw();

}

// Callback to prompt the user and exit to the main menu
static void force_quit(Fl_Widget* btn, void*) {
    // Ask the question and let user choose yes or no.
    switch(fl_choice("Do you want to give up and quit?", "No", "Yes", 0)) {
        case 1: // Yes
            show_main();
    }
}

// Callback function to exit the program.
static void cb_exit(Fl_Widget* btn, void*) {
    exit(0);
}

// Hide all elements in the window.
static void hideall() {
    for (int i = 0; i < win->children(); ++i) {
        win->child(i)->hide();
    }
    // Also remove the demo animation in the splash screen
    Fl::remove_timeout(anim_demo);
}


// function to initialize the configuration file. The load argument indicates
// whether to load the config from file. Set it to false resets the
// configuration file.
static void init_config(bool load = true) {
    delete config;
    config = new ConfigParser("leaderboard.conf");
    if (load) {
        config->load();
    }

    // Set the default configuration values
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

    selected_img_game = config->get<int>("selected_img");
}


// ***** ------------------- *****
// **     The Main Function     **
// ***** ------------------- *****
int main(int argc, char **argv) {
    // Seed random number generator
    srand(time(nullptr));

    // Initialize configuration file
    init_config();

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
