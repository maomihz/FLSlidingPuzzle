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
    int size = game->board().size();
    int grid = h() / size;
    fl_font(FL_BOLD, 36 - 2 * size);
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            int num = game->board().at(i,j);
            const char* numstr = std::to_string(num).c_str();
            if (num != 0) {
                fl_draw(numstr,
                    x() + i * grid, y() + j * grid,
                    grid, grid, FL_ALIGN_INSIDE);
                fl_rect(x() + i * grid, y() + j * grid, grid, grid);
            }
        }
    }
}

// Handle the keyboard event
int GameBoard::handle(int event) {
    // The event only happens of it is a keyboard event,
    // the game is still going on.
    if (event == FL_KEYBOARD && !game->board().win()) {
        switch(Fl::event_key()) {
            case 'w': case 'k': case FL_Up:
                game->up();
                break;
            case 's': case 'j': case FL_Down:
                game->down();
                break;
            case 'a': case 'h': case FL_Left:
                game->left();
                break;
            case 'd': case 'l': case FL_Right:
                game->right();
                break;
            case 'r':
                game->new_game();
                break;
        }
        redraw();
        if (game->board().win()) {
            fl_alert("You win!");
        }
    }
    return 1;
}
