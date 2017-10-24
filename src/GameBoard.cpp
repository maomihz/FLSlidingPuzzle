#include "GameBoard.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

void GameBoard::draw() {
    // Call the draw function of the parent
    Fl_Box::draw();
    // Fill the background
    fl_color(FL_BACKGROUND_COLOR);
    fl_rectf(x(),y(),w(),h());

    // Draw the numbers
    fl_color(FL_BLACK);
    int size = game.board().size();
    int grid = h() / size;
    fl_font(FL_BOLD, 36 - 2 * size);
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            int num = game.board().at(i,j);
            const char* numstr = std::to_string(num).c_str();
            if (num != 0) {
                fl_draw(numstr,
                    x() + i * grid, y() + j * grid,
                    grid, grid, FL_ALIGN_INSIDE);
                fl_rect(x() + i * grid, y() + j * grid, grid, grid);
            }
        }
    }

    // Draw Other stuff
    fl_font(fl_font(), 15);
    fl_draw("Steps",
        x() + 500, y() + 170,
        100, 50, FL_ALIGN_INSIDE);
    fl_draw(std::to_string(game.steps()).c_str(),
        x() + 500, y() + 200,
        100, 50, FL_ALIGN_INSIDE);
    fl_draw("Time",
        x() + 500, y() + 230,
        100, 50, FL_ALIGN_INSIDE);
    int duration = game.duration() / 1000;
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << duration / 60;
    ss << ":";
    ss << std::setw(2) << std::setfill('0') << duration % 60;
    fl_draw(ss.str().c_str(),
        x() + 500, y() + 260,
        100, 50, FL_ALIGN_INSIDE);
}

// Handle the keyboard event
int GameBoard::handle(int event) {
    std::cout << event << std::endl;
    // The event only happens of it is a keyboard event,
    // the game is still going on.
    if (event == FL_KEYBOARD && !game.board().win()) {
        switch(Fl::event_key()) {
            case 'w': case 'k': case FL_Up:
                game.up();
                break;
            case 's': case 'j': case FL_Down:
                game.down();
                break;
            case 'a': case 'h': case FL_Left:
                game.left();
                break;
            case 'd': case 'l': case FL_Right:
                game.right();
                break;
            case 'r':
                game.new_game();
                break;
        }
        redraw();
        if (game.board().win()) {
            fl_alert("You win!");
        }
        return 0;
    }
}
