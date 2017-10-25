#include "board.h"
#include <chrono>

#pragma once

using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::duration;


// Some common manipulation used for an actual sliding puzzle game
namespace SPuzzle {
    class Game {
    private:
        Board board_;          // The pointer to the game board
        Board solution_;       // The solution of the current game board
        int steps_;            // Number of moves
        bool paused_;
        bool started_;         // Whether the game has started or not

        // The time the game lasts is the current time minus the starting
        // time, not including the total pause. After each pause ends,
        // the number of miliseconds are added to the total pause duration.
        milliseconds start_time;     // Starting time of the game
        milliseconds pause_start;
        milliseconds pause_duration; // Total duration of the pause

        milliseconds now() const {
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
        void start();        // Start the game. The game automatically start
                             // when the player makes the first move. Manually
                             // calling start resets the timer.

        // Control the game
        void up();
        void down();
        void left();
        void right();

        Board board();
        Board solution();
        int steps() const;
        int duration() const; // calculated duration of the game in milliseconds
        bool paused() const;
        bool started() const;
    };
}
