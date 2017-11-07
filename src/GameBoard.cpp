#include "GameBoard.h"

void GameBoard::draw() {
    Fl_Box::draw();

    // Refresh the background first so that the drawings won't overlap with
    // each other.
    fl_color(FL_BACKGROUND_COLOR);
    fl_rectf(x(),y(),w(),h());
    fl_line_style(FL_SOLID, 2);

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
            if (num != 0) {
                int xx = x() + i * grid;
                int yy = y() + j * grid;

                // If there is an ongoing animation, then do the calculation
                if (anim_run >= 0 && (Point(i,j) == anim_end)) {
                    xx -= (anim_start.x - i) * grid * (1 - anim_run);
                    yy -= (anim_start.y - j) * grid * (1 - anim_run);
                }
                image->draw(
                    xx, yy,
                    grid - 2,         // Width, gap is needed for visual effect
                    grid - 2,         // Height
                    (num - 1) % size * grid,  // Starting X of the image
                    (num - 1) / size * grid); // Starting Y of the image

                // If the number is in correct location, draw green
                // otherwise draw red
                if (num == j * size + i + 1) {
                    fl_rect(xx,yy,grid,grid,FL_GREEN);
                } else {
                    fl_rect(xx,yy,grid,grid,FL_RED);
                }

                if (i == hover.x && j == hover.y) {
                    fl_rect(xx + 3,yy + 3,grid - 6,grid - 6,FL_YELLOW);
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
    // This part handles keyboard event
    if (event == FL_KEYBOARD || event == FL_PUSH) {
        if (anim_run >= 0) {
            return 1;
        }
        // Prevent operation if the game is in winning position or
        // is paused
        using namespace SPuzzle;
        if (!game->win() && !game->lose() && !game->paused()) {
            // *** KEYBOARD EVENT ***
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
                redraw();
            }
            redraw();
            // After the movement, check if the game is winning
            if (game->win()) {
                fl_alert("You win!");
            } else if (game->lose()) {
                fl_alert("You lost!");
            }
        }
        // Regardless of what, press r will restart the game
        if (Fl::event_key() == 'r') {
            game->new_game();
        }
    }
    // Update hover location
    if (event == FL_MOVE) {
        int grid = h() / game->board().size();
        int x_ = Fl::event_x() - x();
        int y_ = Fl::event_y() - y();
        hover.x = x_ / grid;
        hover.y = y_ / grid;
        redraw();
    } else if (event == FL_LEAVE) {
        hover.x = -1;
        redraw();
    }

    // Always return 1 to represent the event is received, although not
    // always have effect
    return 1;
}
