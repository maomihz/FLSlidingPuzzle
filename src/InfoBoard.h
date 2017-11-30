#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <vector>
#include <string>
#include "game.h"
#include "configparser.h"

using std::vector;
using std::string;

// The InfoBoard class is used to display information about the game and is
// seperated from the main board. Information include the duration, number of
// steps, and the score. When created, the same pointer of a Game object as the
// GameBoard must be passed in in order to access the data correctly.
class InfoBoard : public Fl_Box {
private:
    vector<int> scores;
    vector<string> players;
public:
    SPuzzle::Game* game;   // The game the board represents
    ConfigParser* config; // The global configuration,
                          // used to display high score
    InfoBoard(int x, int y, int w, int h, SPuzzle::Game* game, ConfigParser* config)
        : Fl_Box(x, y, w, h, NULL),
        game(game),
        config(config) {}

    // Override the draw function and event handle function
    void draw();

    // This is used to update the leaderboard. It copies the vector from
    // configuration. Called when a new game starts
    void update();
};
