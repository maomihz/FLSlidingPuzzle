#include "game.h"

using namespace SPuzzle;

// ====== Constructors & Destructors ======
Game::Game(int size) :
    board_(size),    // A newly created board is in order unless shuffle() is
    solution_(size), // explictly called
    last_(Point(size - 1, size - 1)),
    steps_(0)
{
    new_game();
}

Game::~Game() {}


// ===== Function Implementations =====
// Start a new game, shuffle the board and reset variables.
void Game::new_game() {
    reset();
    shuffle();
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
    if (move(UP)) ++steps_;
    if (!started_) start();
}
void Game::down() {
    if (move(DOWN)) ++steps_;
    if (!started_) start();
}
void Game::left() {
    if (move(LEFT)) ++steps_;
    if (!started_) start();
}
void Game::right() {
    if (move(RIGHT)) ++steps_;
    if (!started_) start();
}


// Check whether the board can move in a particular direction
// If the location which is going to swap with the empty space
// is valid then the move is valid.
bool Game::can_move(int dir) const {
    Point next = space_ + DIRECTIONS[dir];
    return board_.valid(next);
}


// To make an actual move. If the direction is not moveable
// then the function would do nothing and return false.
// If a move is successfully made the function returns true.
bool Game::move(int dir) {
    // Still check validity first
    if (!can_move(dir)) return false;

    Point next = DIRECTIONS[dir] + space_;
    board_.swap(space_, next);
    space_ = next;
    return true;
}


// Resets the board to the initial state.
// The initial state is the winning state.
void Game::reset() {
    // Assign the numbers in order, except the last one
    for (int i = 0; i < board_.repr(last_); ++i) {
        board_.at(i) = i + 1;
    }
    board_.at(last_) = 0;    // Set the last one to zero
    space_ = last_;    // Set the space location to the last one
}



// Shuffle the board
// The shuffle function don't care if the board is
// in the initial state or not
void Game::shuffle() {
    // Restore the location of empty space first
    board_.swap(space_, last_);
    space_ = last_;

    // Trust the rand() function and do the shuffling
    // Skip the last location
    for (int i = 0; i < board_.repr(last_) - 1; ++i) {
        // It is valid if the chosen point is itself.
        int to_swap = rand() % (board_.repr(last_) - i) + i;
        board_.swap(i, to_swap);
    }

    while (!solvable()) {
        int loc1 = rand() % board_.repr(last_);
        int loc2 = rand() % board_.repr(last_);
        board_.swap(loc1, loc2);
    }
}



// Check how many tiles are in the winning position.
int Game::correct_count() const {
    int count = 0;
    for (int i = 0; i < board_.repr(last_); ++i) {
        if (board_.at(i) == i + 1) ++count;
    }
    return count;
}

// Check whether the layout is equal to the winning position.
bool Game::win() const {
    // Check everything except the last one
    // If everything except the last one is equal to the
    // winning position then the last one must be zero
    for (int i = 0; i < board_.repr(last_); ++i) {
        if (board_.at(i) != i + 1) return false;
    }
    // Otherwise, return true
    return true;
}


// Check whether the game board is solvable
// http://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
bool Game::solvable() const {
    int count = 0;
    for (int i = 0; i < board_.repr(last_); ++i) {
        for (int j = i + 1; j < board_.len(); ++j) {
            if (board_.at(j) && board_.at(i) && board_.at(i) > board_.at(j)) {
                ++ count;
            }
        }
    }
    if (board_.size() & 1) {
        return !(count & 1);
    } else {
        if ((board_.size() - space_.y) & 1) {
            return !(count & 1);
        } else {
            return count & 1;
        }
    }
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
