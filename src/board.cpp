#include "board.h"
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace SPuzzle;

// ========================================
// ------------ Constructors --------------
// ========================================

// Initialize a board with a specified size
Board::Board(int size) :
    _size(size),
    _len(size * size),
    _last(Point(size - 1, size - 1))
{
    board = new int[_len];  // Initialize to a long array
    reset();                // Reset the state
}

// Copy constructor
Board::Board(Board &another) : Board(another.size()) {
    for (int i = 0; i < len(); ++i) {
        at(i) = another.at(i);
    }
    _space = another._space;
}

// Destructor
Board::~Board() {
    delete [] board;
}

// ================================================
// ------- Public Function implementations --------
// ================================================

// Get the content of a particular coordinate.
// Returns an integer that represents the content.
int& Board::at(int x, int y) const {
    if (!valid(x, y)) {
        throw std::out_of_range("Invalid coordinate");
    }
    // Return the content in the array
    return board[repr(x, y)];
}
int& Board::at(int repr) const {
    return at(to_point(repr));
}
int& Board::at(Point p) const {
    return at(p.x, p.y);
}




// Check whether the board can move in a particular direction
// If the location which is going to swap with the empty space
// is valid then the move is valid.
bool Board::can_move(int dir) const {
    Point next = _space + DIRECTIONS[dir];
    return valid(next);
}


// To make an actual move. If the direction is not moveable
// then the function would do nothing and return false.
// If a move is successfully made the function returns true.
bool Board::move(int dir) {
    // Still check validity first
    if (!can_move(dir)) return false;

    Point next = DIRECTIONS[dir] + _space;
    swap(_space, next);
    _space = next;
    return true;
}
bool Board::up() {return move(UP);}
bool Board::down() {return move(DOWN);}
bool Board::left() {return move(LEFT);}
bool Board::right() {return move(RIGHT);}



// Resets the board to the initial state.
// The initial state is the winning state.
void Board::reset() {
    // Assign the numbers in order, except the last one
    for (int i = 0; i < repr(_last); ++i) {
        at(i) = i + 1;
    }
    at(_last) = 0;    // Set the last one to zero
    _space = _last;    // Set the space location to the last one
}



// Shuffle the board
// The shuffle function don't care if the board is
// in the initial state or not
void Board::shuffle() {
    // Restore the location of empty space first
    swap(_space, _last);
    _space = _last;

    // Trust the rand() function and do the shuffling
    // Skip the last location
    for (int i = 0; i < repr(_last) - 1; ++i) {
        // It is valid if the chosen point is itself.
        int to_swap = rand() % (repr(_last) - i) + i;
        swap(i, to_swap);
    }

    while (!solvable()) {
        int loc1 = rand() % repr(_last);
        int loc2 = rand() % repr(_last);
        swap(loc1, loc2);
    }
}




// Check whether the layout is equal to the winning position.
bool Board::win() const {
    // Check everything except the last one
    // If everything except the last one is equal to the
    // winning position then the last one must be zero
    for (int i = 0; i < repr(_last); ++i) {
        if (at(i) != i + 1) {
            std::cout << at(i) << "!=" << i+1 << std::endl;
            return false;
        }
    }
    // Otherwise, return true
    return true;
}


// Check whether the game board is solvable
// http://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
bool Board::solvable() const {
    int count = 0;
    for (int i = 0; i < repr(_last); ++i) {
        for (int j = i + 1; j < _len; ++j) {
            if (board[j] && board[i] && board[i] > board[j]) {
                ++ count;
            }
        }
    }
    if (_size & 1) {
        return !(count & 1);
    } else {
        if ((_size - _space.x) & 1) {
            return !(count & 1);
        } else {
            return count & 1;
        }
    }
}



// ================================================
// ------- Helper Functions implementations -------
// ================================================
// Convert the "internal" representation to point or back
int Board::repr(int x, int y) const {
    return x * _size + y;
}
int Board::repr(Point p) const {
    return repr(p.x, p.y);
}
Point Board::to_point(int repr) const {
    return Point(repr / _size, repr % _size);
}




// Swap the content of one coordinate with another.
void Board::swap(int x1, int y1, int x2, int y2) {
    swap(Point(x1, y1), Point(x2, y2));
}
// Swap two representations
void Board::swap(int repra, int reprb) {
    swap(to_point(repra), to_point(reprb));
}
void Board::swap(Point a, Point b) {
    // Both point a and point b need to be valid
    if (!(valid(a) && valid(b))) {
        throw std::out_of_range("Invalid swap.");
    }

    // Swap the content of the two coordinates
    // Only do swap if the points are unequal
    if (a != b) {
 	    int tmp = at(a);
        at(a) = at(b);
        at(b) = tmp;
    }
}



// Check whether a particular point on the board is valid.
// If the point is within the borders then the point is valid.
// Check both x coordinate and y coordinate
bool Board::valid(int x, int y) const {
    return (x >= 0 && x < _size && y >= 0 && y < _size);
}
bool Board::valid(int repr) const {
    return valid(to_point(repr));
}
bool Board::valid(Point p) const {
    return valid(p.x, p.y);
}





// =====================================
// ------- Some other functions --------
// =====================================

std::ostream& operator<<(std::ostream& os, const Board& b) {
    for (int i = 0; i < b.len(); ++i) {
        os << std::setw(3) << b.at(i);
        if ((i + 1) % b.size() == 0) {
            os << std::endl;
        }
    }
    return os;
}
