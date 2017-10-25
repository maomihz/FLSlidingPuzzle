#include "InfoBoard.h"
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
    fl_draw("Steps", x(), y(),
        100, 50, FL_ALIGN_INSIDE);
    fl_draw("Time", x(), y() + 100,
        100, 50, FL_ALIGN_INSIDE);

    fl_draw(std::to_string(game->steps()).c_str(),
        x(), y() + 50,
        100, 50, FL_ALIGN_INSIDE);

    // build the time
    int duration = game->duration();
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << duration / 60000;
    ss << ":";
    ss << std::setw(2) << std::setfill('0') << duration / 1000 % 60;
    fl_draw(ss.str().c_str(),
        x(), y() + 150,
        100, 50, FL_ALIGN_INSIDE);
}
