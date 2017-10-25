#include "game.h"

using namespace SPuzzle;

// ====== Constructors & Destructors ======
Game::Game(int size) :
    board_(size),
    solution_(size),
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
    started_ = false;
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
int Game::duration() const {
    // If the game has not started then always return 0
    if (!started_) {
        return 0;
    }
    // Otherwise return the actual time
    return (now() - start_time - pause_duration).count();
}
bool Game::paused() const { return paused_; }
bool Game::started() const { return started_; }
