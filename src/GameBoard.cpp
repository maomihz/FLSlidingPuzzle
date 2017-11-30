#include "GameBoard.h"

void GameBoard::draw() {
    Fl_Box::draw();

    // Refresh the background first so that the drawings won't overlap with
    // each other.
    fl_color(FL_BACKGROUND_COLOR);
    fl_rectf(x(),y(),w(),h());

    // Set the border style
    fl_line_style(FL_SOLID, 2);

    // Initialize some variables
    int size = game->board().size();  // The size of the game board
    int grid = h() / size;            // The width of each square. Assume
                                      // height to be less than width.

    // Drawing the whole image (solution) if the game is paused, and do nothing
    // else.
    if (game->paused()) {
        image->draw(x(), y());
        return;
    }


    // Drawing if the game is not paused
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
            // and draw each part. Ignore the space.
            if (num != 0) {
                // Starting x, y for each square
                int xx = x() + i * grid;
                int yy = y() + j * grid;

                // If there is an ongoing animation, then do the calculation
                if (anim_run >= 0 && (Point(i,j) == anim_end)) {
                    xx -= (anim_start.x - i) * grid * (1 - anim_run);
                    yy -= (anim_start.y - j) * grid * (1 - anim_run);
                }

                // Draw the actual cropped image
                image->draw(
                    xx, yy,
                    grid - 2,         // Width, gap is needed for visual effect
                    grid - 2,         // Height
                    (num - 1) % size * grid,  // Starting X of the image
                    (num - 1) / size * grid); // Starting Y of the image

                // Draw borders.
                // Green for  "correct",
                // Red for    "incorrect",
                // Yellow for "hover",
                // Cyan for   "hint".
                // A game in "Read Only" state does not need borders.
                if (!readonly_) {
                    if (num == j * size + i + 1) {
                        fl_rect(xx,yy,grid,grid,FL_GREEN);
                    } else {
                        fl_rect(xx,yy,grid,grid,FL_RED);
                    }

                    if (i == hover.x && j == hover.y) {
                        fl_rect(xx + 3,yy + 3,grid - 6,grid - 6,FL_YELLOW);
                    }
                    if (i == hint.x && j == hint.y) {
                        fl_rect(xx + 3,yy + 3,grid - 6,grid - 6,FL_CYAN);
                    }
                }
            }
        }
    }
}


static void run_anim(void* gameboard) {
    GameBoard* gb = (GameBoard*) gameboard;
    if (gb->anim_run >= 1) {
        gb->anim_run = -1;
    } else {
        gb->anim_run += 0.5;
        if (gb->anim_run > 1) {
            gb->anim_run = 1;
        }
        Fl::repeat_timeout(0.01, run_anim, gameboard);
    }
    gb->redraw();
}

void GameBoard::move(SPuzzle::Direction dir) {
    anim_start = game->space() - SPuzzle::DIRECTIONS[dir];
    anim_end = game->space();
    anim_run = 0;
    game->move(dir);
    Fl::add_timeout(0.01, run_anim, this);
}

using namespace SPuzzle;
void GameBoard::click(Point p) {
    if (game->get_move(UP) == p) {
        move(UP);
    } else if (game->get_move(DOWN) == p) {
        move(DOWN);
    } else if (game->get_move(LEFT) == p) {
        move(LEFT);
    } else if (game->get_move(RIGHT) == p) {
        move(RIGHT);
    }
}

// Handle the keyboard event
int GameBoard::handle(int event) {
    // If the board is "Read Only", or if the game is paused,
    // then do not handle any events
    if (readonly_ || game->paused()) {
        return 1;
    }

    // This part handles keyboard event
    if (event == FL_KEYBOARD || event == FL_PUSH) {
        take_focus();
        // Cancel operation if there is an ongoing animation
        if (anim_run >= 0) {
            return 1;
        }
        using namespace SPuzzle;
        // Prevent operation if the game is in winning position
        if (!game->win() && !game->lose()) {
            // *** KEYBOARD EVENT ***
            // Mark here that before the movement whether the game is started.
            bool started = game->started();
            if (event == FL_KEYBOARD) {
                // w/s/a/d are for gamers
                // h/j/k/l are for vimers
                // up/down/left/right are for noobs
                switch(Fl::event_key()) {
                    case 'w': case 'k': case FL_Up:
                        move(UP);
                        break;
                    case 's': case 'j': case FL_Down:
                        move(DOWN);
                        break;
                    case 'a': case 'h': case FL_Left:
                        move(LEFT);
                        break;
                    case 'd': case 'l': case FL_Right:
                        move(RIGHT);
                        break;
                }
            // *** MOUSE EVENT ***
            } else if (event == FL_PUSH) {
                int grid = h() / game->board().size();
                int x_ = Fl::event_x() - x();
                int y_ = Fl::event_y() - y();
                click(Point{x_ / grid, y_ / grid});
            }
            // After the movement, check if the game is winning
            if (game->win() || game->lose()) {
                do_callback();
            }
            redraw();
        }
        // Regardless of what, pressing r will restart the game
        // Disallow the action for now
        if (Fl::event_key() == 'r' && false) {
            game->new_game();
        }
    }
    // Update hover location
    if (event == FL_MOVE) {
        int grid = h() / game->board().size();
        int x_ = Fl::event_x() - x();
        int y_ = Fl::event_y() - y();
        int x_grid = x_ / grid;
        int y_grid = y_ / grid;
        // Try to prevent unnecessary redraw
        bool need_redraw = hover.x != x_grid || hover.y != y_grid;
        if (need_redraw) {
            hover.x = x_ / grid;
            hover.y = y_ / grid;
            redraw();
        }
    } else if (event == FL_LEAVE) {
        hover.x = -1;
        redraw();
    }

    // Always return 1 to represent the event is received, although not
    // always have effect
    return 1;
}
