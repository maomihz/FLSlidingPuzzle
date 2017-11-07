#include "GameBoard.h"
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
}
