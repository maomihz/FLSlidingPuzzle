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
    start_time = now();
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


void Game::up() {
    if (board_.move(UP)) ++steps_;
}
void Game::down() {
    if (board_.move(DOWN)) ++steps_;
}
void Game::left() {
    if (board_.move(LEFT)) ++steps_;
}
void Game::right() {
    if (board_.move(RIGHT)) ++steps_;
}



// ====== Accessers =======
Board Game::board() { return board_; }
Board Game::solution() { return solution_; }
int Game::steps() const { return steps_; }
int Game::duration() {
    cout << start_time << ":" << now() << endl;
    return (now() - start_time - pause_duration).count() / 1000;
}
bool Game::paused() const { return paused_; }
