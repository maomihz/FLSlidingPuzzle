#include "board.h"
#include <chrono>

#pragma once

using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;


// Some common manipulation used for an actual sliding puzzle game
namespace SPuzzle {
    class Game {
    private:
        Board* _board;          // The pointer to the game board
        Board* _solution;       // The solution of the current game board
        int _steps;             // Number of moves
        bool _paused;

        // The time the game lasts is the current time minus the starting
        // time, not including the total pause. After each pause ends,
        // the number of miliseconds are added to the total pause duration.
        milliseconds start_time;     // Starting time of the game
        milliseconds pause_start;
        milliseconds pause_duration; // Total duration of the pause

        milliseconds now() {
            return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        }
    public:
        Game(int size = 4);
        ~Game();

        // When a new game is started, set the starting time to the current
        // time and reset everything else, shuffle the board.
        // The pause function of this class is only used to count the
        // time, and it will not prevent the board from moving.
        void new_game();     // Start a new game
        void pause();        // Pause the game
        void resume();       // Resume the game

        Board* board();
        Board* solution();
        int steps();
        int duration();         // calculated duration of the game in seconds
        bool paused();

    };
}
