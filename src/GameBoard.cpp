#include "GameBoard.h"
#include <iostream>

void GameBoard::draw() {
    Fl_Box::draw();
    fl_line_style(FL_SOLID, 8);
    fl_color(FL_WHITE);
    fl_rectf(x(),y(),w(),h());
    fl_color(FL_BLACK);

    fl_font(FL_BOLD, 29);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int num = game.board().at(i,j);
            const char* numstr = std::to_string(num).c_str();
            if (num != 0)
                fl_draw(numstr, x() + j * 100, y() + i * 100,
                100, 100, FL_ALIGN_INSIDE);
        }
    }
}


int GameBoard::handle(int event) {
    std::cout << event << std::endl;
    if (event == FL_KEYBOARD && !game.board().win()) {
        switch(Fl::event_key()) {
            case 'w': case 'k': case FL_Up:
                game.up();
                redraw();
                break;
            case 's': case 'j': case FL_Down:
                game.down();
                redraw();
                break;
            case 'a': case 'h': case FL_Left:
                game.left();
                redraw();
                break;
            case 'd': case 'l': case FL_Right:
                game.right();
                redraw();
                break;
        }
        if (game.board().win()) {
            fl_alert("You win!");
        }
        std::cout << game.board();
    }
}
