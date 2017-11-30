#include "InfoBoard.h"
#include "util.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

void InfoBoard::draw_steps() {
    // Build the step
    std::stringstream ss_steps;
    // Depending on whether the game is in "puzzle mode" or "free mode",
    // it draws different text.
    if (game->steps_limit() > 0) {
        fl_draw("Steps Left", x(), y() + 25, 100, 25, FL_ALIGN_INSIDE);
        ss_steps << game->steps_remain();
    } else {
        fl_draw("Steps", x(), y() + 25, 100, 25, FL_ALIGN_INSIDE);
        ss_steps << game->steps();
    }
    fl_draw(ss_steps.str().c_str(),
        x(), y() + 50,
        100, 25, FL_ALIGN_INSIDE);
}


void InfoBoard::draw_progress() {
    // Show how many tiles are in the correct location
    fl_draw("Progress", x(), y() + 110, 100, 25, FL_ALIGN_INSIDE);
    std::stringstream ss_progress;
    ss_progress << game->correct_count();
    ss_progress << "/";
    ss_progress << game->board().len() - 1;
    fl_draw(ss_progress.str().c_str(), x(), y() + 135, 100, 25, FL_ALIGN_INSIDE);
}


void InfoBoard::draw_time() {
    // build the game time
    int duration = game->duration();
    std::stringstream ss_time;
    ss_time << std::setw(2) << std::setfill('0') << duration / 60000;
    ss_time << ":";
    ss_time << std::setw(2) << std::setfill('0') << duration / 1000 % 60;
    fl_draw("Time", x(), y() + 200,
        100, 25, FL_ALIGN_INSIDE);
    fl_draw(ss_time.str().c_str(),
        x(), y() + 225,
        100, 25, FL_ALIGN_INSIDE);
}


void InfoBoard::draw_leaderboard() {
    // Draw the high scores
    fl_draw("LEADERBOARD", x() + 125, y() + 5, 100, 25, FL_ALIGN_INSIDE);
    int score = game->score();
    // Only take the first 12 characters. Player is not expected to put
    // very long name.
    string player = config->get<string>("player.name").substr(0,12);

    for (string::size_type i = 0; i < scores.size(); ++i) {
        string p = players.at(i).substr(0,12);
        string s = std::to_string(scores.at(i));
        // If the string is empty then put <Empty>
        if (!p.length()) p = "<Empty>";
        fl_draw(p.c_str(),
            x() + 115, y() + 5 + 40 * (i + 1),
            75, 25, FL_ALIGN_LEFT);
        fl_draw(s.c_str(),
            x() + 210, y() + 5 + 40 * (i + 1),
            25, 25, FL_ALIGN_RIGHT);
    }

    // On the bottom draw the player score in red.
    fl_color(FL_RED);
    fl_draw(player.c_str(),
        x() + 115, y() + 40 * 6,
        75, 25, FL_ALIGN_LEFT);
    fl_draw(std::to_string(score).c_str(),
        x() + 210, y() + 40 * 6,
        25, 25, FL_ALIGN_RIGHT);
}


void InfoBoard::draw() {
    // Call the draw function of the parent
    Fl_Box::draw();

    // Set the text
    fl_color(FL_BLACK);
    fl_font(fl_font(), 15);

    // Draw Everything
    draw_steps();
    draw_progress();
    draw_time();
    draw_leaderboard();
}

void InfoBoard::update() {
    scores = config->get<vector<int>>(game->description() + ".scores");
    players = config->get<vector<string>>(game->description() + ".players");
}
