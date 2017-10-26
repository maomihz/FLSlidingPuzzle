#include "game.h"

using namespace SPuzzle;

// ====== Constructors & Destructors ======
Game::Game(int size) :
    board_(size),    // A newly created board is in order unless shuffle() is
    solution_(size), // explictly called
    steps_(0)
{
    new_game();
}

Game::~Game() {}


// ===== Function Implementations =====
// Start a new game, shuffle the board and reset variables.
void Game::new_game() {
    board_.shuffle();
    steps_ = 0;
    started_ = false;    // When a new game is started, the started flag need
                         // to be set to false because at this time the timer
                         // should not run until the first move is made
    pause_duration = milliseconds::zero();
}

void Game::pause() {
    // Only take action if the game is not paused
    if (!paused_) {
        pause_start = now();
        paused_ = true;
    }
}

void Game::resume() {
    // Only take action if the game is paused
    if (paused_) {
        pause_duration += (now() - pause_start);
        paused_ = false;
    }
}

// The start function just resets the timer
void Game::start() {
    start_time = now();
    started_ = true;
}



void Game::up() {
    if (board_.move(UP)) ++steps_;
    if (!started_) start();
}
void Game::down() {
    if (board_.move(DOWN)) ++steps_;
    if (!started_) start();
}
void Game::left() {
    if (board_.move(LEFT)) ++steps_;
    if (!started_) start();
}
void Game::right() {
    if (board_.move(RIGHT)) ++steps_;
    if (!started_) start();
}



// ====== Accessers =======
Board Game::board() { return board_; }
Board Game::solution() { return solution_; }
int Game::steps() const { return steps_; }
bool Game::paused() const { return paused_; }
bool Game::started() const { return started_; }
// Return the duration of the game in milliseconds. The duration is not always
// correct and should not be used when the game has ended or is paused.
int Game::duration() const {
    // If the game has not started then always return 0. At this time the timer
    // could be anything.
    if (!started_) {
        return 0;
    }
    // Otherwise return the actual time. It is the difference of the starting
    // time, not including total pause duration.
    return (now() - start_time - pause_duration).count();
}
