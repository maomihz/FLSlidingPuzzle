#include "GameBoard.h"

void GameBoard::draw() {
    Fl_Box::draw();

    // Refresh the background first so that the drawings won't overlap with
    // each other.
    fl_color(FL_BACKGROUND_COLOR);
    fl_rectf(x(),y(),w(),h());

    // Draw the numbers
    int size = game->board().size();  // The size of the game board
    int grid = h() / size;            // The width of each square. Assume
                                      // height to be less than width.
    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            int num = game->board().at(i,j);
            // If the game is in winning position, draw everything including
            // the missing corner. It converts the "0" that is used to represent
            // space to the length of the board, so that the last piece draws
            // correctly.
            if (game->win() && num == 0) {
                num = game->board().len();
            }
            // If the game is not in winning position, then it crops the image
            // and draw each part.
            if (num != 0)
                image->draw(
                    x() + i * grid,   // X
                    y() + j * grid,   // Y
                    grid - 2,         // Width, gap is needed for visual effect
                    grid - 2,         // Height
                    (num - 1) % size * grid,  // Starting X of the image
                    (num - 1) / size * grid); // Starting Y of the image
        }
    }
}

// Handle the keyboard event
int GameBoard::handle(int event) {
    // This part handles keyboard event
    if (event == FL_KEYBOARD) {
        // Prevent operation if the game is in winning position or
        // is paused
        if (!game->win() && !game->paused()) {
            // w/s/a/d are for gamers
            // h/j/k/l are for vimers
            // up/down/left/right are for noobs
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
            }
            redraw();
            // After the movement, check if the game is winning
            if (game->win()) {
                fl_alert("You win!");
            }
        }
        // Regardless of what, press r will restart the game
        if (Fl::event_key() == 'r') {
            game->new_game();
        }
    }

    // Always return 1 to represent the event is received, although not
    // always have effect
    return 1;
}
