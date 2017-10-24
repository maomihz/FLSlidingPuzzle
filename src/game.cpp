#include "game.h"

using namespace SPuzzle;

// ====== Constructors & Destructors ======
Game::Game(int size) :
    _board(size),
    _solution(size),
    _steps(0)
{
    new_game();
}

Game::~Game() {
    // delete _board;
    // delete _solution;
}


// ===== Function Implementations =====
void Game::new_game() {
    _board.shuffle();
    _steps = 0;
    start_time = now();
}

void Game::pause() {
    // Only take action if the game is not paused
    if (!_paused) {
        pause_start = now();
        _paused = true;
    }
}

void Game::resume() {
    // Only take action if the game is paused
    if (_paused) {
        pause_duration += (now() - pause_start);
        _paused = false;
    }
}


void Game::up() {
    if (_board.up()) ++_steps;
}
void Game::down() {
    if (_board.down()) ++_steps;
}
void Game::left() {
    if (_board.left()) ++_steps;
}
void Game::right() {
    if (_board.right()) ++_steps;
}



// ====== Accessers =======
Board Game::board() { return _board; }
Board Game::solution() { return _solution; }
int Game::steps() const { return _steps; }
int Game::duration() {
    return (now() - start_time - pause_duration).count();
}
bool Game::paused() const { return _paused; }
