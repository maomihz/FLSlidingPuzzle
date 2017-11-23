#include "board.h"
#include <chrono>
#include <vector>

#pragma once

using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::chrono::duration;


// Some common manipulation used for an actual sliding puzzle game
namespace SPuzzle {
    // ===== Some constants ======
    // Constants to represent moving direction
    typedef int Direction;
    const Direction UP = 0;
    const Direction DOWN = 1;
    const Direction LEFT = 2;
    const Direction RIGHT = 3;

    // A map for constant to point. These points can be added to a existing
    // point to calculate the coordinate the point is moving to.
    // The direction is actually reversed because if you are moving up
    // then the space is moving down.
    const Point DIRECTIONS[] = {
        Point(0, 1),     // Up
        Point(0, -1),    // Down
        Point(1, 0),     // Left
        Point(-1, 0)     // Right
    };


    class Game {
    private:
        // Primary storage
        Board board_;          // The pointer to the game board
        Board solution_;       // The solution of the current game board

        // Variables for easy access
        Point last_;           // The last point in the board
        Point space_;          // The index of empty space
        int steps_;            // Number of moves
        int steps_limit_;      // This is used to describe the game mode. On a
                               // free mode the steps limit should be negative.
                               // For a puzzle mode the steps limit should be
                               // non-negative. Step limit 0 for a puzzle mode
                               // means the game is over.
        bool paused_;
        bool started_;         // Whether the game has started or not

        std::string description_; // The description of the game

        // The time the game lasts is the current time minus the starting
        // time, not including the total pause. After each pause ends,
        // the number of miliseconds are added to the total pause duration.
        milliseconds start_time;     // Starting time of the game
        milliseconds pause_start;
        milliseconds pause_duration; // Total duration of the pause

        milliseconds now() const {   // Return the current time in milliseconds
            return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        }
    public:
        Game(int size = 4); // Constructs a default board
        ~Game();

        // When a new game is started, set the starting time to the current
        // time and reset everything else, shuffle the board.
        // The pause function of this class is only used to count the
        // time, and it will not prevent the board from moving.
        void new_game(std::string description = "");     // Start a new game
        void new_game(std::vector<int> data, int step_limit=-1, std::string description = "");
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

        bool can_move(Direction dir) const;     // Can move or not
        bool move(Direction dir);               // Move in one direction
        Point get_move(Direction dir) const;   // Get the point in the direction

        void reset();             // Reset board to initial location
        void shuffle();           // Shuffle the board
        int correct_count() const;// Count the number of tiles that is in the
                                  // correct location. 0 <= n < len, not
                                  // including the space tile.
        bool win() const;         // Check if the board is in winning position.
                                  // The initial position is always the winning
                                  // postition.
        bool lose() const;        // Check if the game is losing. The game is
                                  // lost if number of steps exceed step limit.


        bool solvable() const;    // Check if the board is solvable
        Direction hint() const;   // Calculate a hint direction based on
                                  // Manhatten distance function
        int score() const;        // Calculate the score

        // These are all accessor functions
        Board board();
        Board solution();
        Point last() const {return last_;}
        Point space() const {return space_;}
        std::string description() const { return description_; }

        int steps() const;
        int steps_remain() const; // Calculated step remain
        int steps_limit() const;
        int duration() const; // calculated duration of the game in milliseconds
        bool paused() const;
        bool started() const;

        bool free_mode() const; // Check the game is free mode or not
        bool puzzle_mode() const; // Check the game is puzzle mode or not
    };
}
