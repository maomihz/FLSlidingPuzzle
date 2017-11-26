#include "GameBoard.h"
#include "util.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

void InfoBoard::draw() {
    // Call the draw function of the parent
    Fl_Box::draw();
    // Fill the background
    fl_color(FL_BACKGROUND_COLOR);
    fl_rectf(x(),y(),w(),h());

    // Draw the text
    fl_color(FL_BLACK);
    fl_font(fl_font(), 15);


    // Build the step
    std::stringstream ss_steps;
    if (game->steps_limit() > 0) {
        fl_draw("Steps Remain", x(), y(), 100, 25, FL_ALIGN_INSIDE);
        ss_steps << game->steps_remain();
    } else {
        fl_draw("Steps", x(), y(), 100, 25, FL_ALIGN_INSIDE);
        ss_steps << game->steps();
    }
    fl_draw(ss_steps.str().c_str(),
        x(), y() + 25,
        100, 25, FL_ALIGN_INSIDE);

    fl_draw("Progress", x(), y() + 75, 100, 25, FL_ALIGN_INSIDE);
    std::stringstream ss_progress;
    ss_progress << game->correct_count();
    ss_progress << "/";
    ss_progress << game->board().len() - 1;
    fl_draw(ss_progress.str().c_str(), x(), y() + 100, 100, 25, FL_ALIGN_INSIDE);

    // build the time
    int duration = game->duration();
    std::stringstream ss_time;
    ss_time << std::setw(2) << std::setfill('0') << duration / 60000;
    ss_time << ":";
    ss_time << std::setw(2) << std::setfill('0') << duration / 1000 % 60;
    fl_draw("Time", x(), y() + 150,
        100, 25, FL_ALIGN_INSIDE);
    fl_draw(ss_time.str().c_str(),
        x(), y() + 175,
        100, 25, FL_ALIGN_INSIDE);

    // Draw the high scores
    fl_draw("LEADERBOARD", x() + 125, y(), 100, 25, FL_ALIGN_INSIDE);
    int score = game->score();
    string player = config->get("player.name");
    vector<int> scores = config->get_v(game->description() + ".scores");
    vector<string> players = config->get_v_str(game->description() + ".players");
    // Magic insertion
    // magic_insert(score, player, scores, players);

    for (string::size_type i = 0; i < scores.size(); ++i) {
        string p = players.at(i);
        string s = std::to_string(scores.at(i));
        if (!p.length()) p = "<Empty>";
        fl_draw(p.c_str(),
            x() + 115, y() + 40 * (i + 1),
            75, 25, FL_ALIGN_LEFT);
        fl_draw(s.c_str(),
            x() + 210, y() + 40 * (i + 1),
            25, 25, FL_ALIGN_RIGHT);
    }
    fl_color(FL_RED);
    fl_draw(player.c_str(),
        x() + 115, y() + 40 * 6,
        75, 25, FL_ALIGN_LEFT);
    fl_draw(std::to_string(score).c_str(),
        x() + 210, y() + 40 * 6,
        25, 25, FL_ALIGN_RIGHT);
}
