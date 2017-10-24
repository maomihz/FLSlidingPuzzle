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
    size_(size),
    len_(size * size),
    last_(Point(size - 1, size - 1))
{
    board = new int[len_];  // Initialize to a long array
    reset();                // Reset the state
}

// Copy constructor
Board::Board(Board &another) : Board(another.size()) {
    for (int i = 0; i < len(); ++i) {
        at(i) = another.at(i);
    }
    space_ = another.space_;
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

// Get the content of a particular coordinate in string
std::string Board::at_str(int x, int y) const {
    return std::to_string(at(x, y));
}
std::string Board::at_str(int repr) const {
    return std::to_string(at(repr));
}
std::string Board::at_str(Point p) const {
    return std::to_string(at(p));
}





// Check whether the board can move in a particular direction
// If the location which is going to swap with the empty space
// is valid then the move is valid.
bool Board::can_move(int dir) const {
    Point next = space_ + DIRECTIONS[dir];
    return valid(next);
}


// To make an actual move. If the direction is not moveable
// then the function would do nothing and return false.
// If a move is successfully made the function returns true.
bool Board::move(int dir) {
    // Still check validity first
    if (!can_move(dir)) return false;

    Point next = DIRECTIONS[dir] + space_;
    swap(space_, next);
    space_ = next;
    return true;
}


// Resets the board to the initial state.
// The initial state is the winning state.
void Board::reset() {
    // Assign the numbers in order, except the last one
    for (int i = 0; i < repr(last_); ++i) {
        at(i) = i + 1;
    }
    at(last_) = 0;    // Set the last one to zero
    space_ = last_;    // Set the space location to the last one
}



// Shuffle the board
// The shuffle function don't care if the board is
// in the initial state or not
void Board::shuffle() {
    // Restore the location of empty space first
    swap(space_, last_);
    space_ = last_;

    // Trust the rand() function and do the shuffling
    // Skip the last location
    for (int i = 0; i < repr(last_) - 1; ++i) {
        // It is valid if the chosen point is itself.
        int to_swap = rand() % (repr(last_) - i) + i;
        swap(i, to_swap);
    }

    while (!solvable()) {
        int loc1 = rand() % repr(last_);
        int loc2 = rand() % repr(last_);
        swap(loc1, loc2);
    }
}



// Check how many tiles are in the winning position.
int Board::correct_count() const {
    int count;
    for (int i = 0; i < repr(last_); ++i) {
        if (at(i) == i + 1) ++count;
    }
    return count;
}

// Check whether the layout is equal to the winning position.
bool Board::win() const {
    // Check everything except the last one
    // If everything except the last one is equal to the
    // winning position then the last one must be zero
    for (int i = 0; i < repr(last_); ++i) {
        if (at(i) != i + 1) return false;
    }
    // Otherwise, return true
    return true;
}


// Check whether the game board is solvable
// http://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/
bool Board::solvable() const {
    int count = 0;
    for (int i = 0; i < repr(last_); ++i) {
        for (int j = i + 1; j < len_; ++j) {
            if (board[j] && board[i] && board[i] > board[j]) {
                ++ count;
            }
        }
    }
    if (size_ & 1) {
        return !(count & 1);
    } else {
        if ((size_ - space_.y) & 1) {
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
    return y * size_ + x;
}
int Board::repr(Point p) const {
    return repr(p.x, p.y);
}
Point Board::to_point(int repr) const {
    return Point(repr % size_, repr / size_);
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
    return (x >= 0 && x < size_ && y >= 0 && y < size_);
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
    for (int y = 0; y < b.size(); ++y) {
        for (int x = 0; x < b.size(); ++x) {
            os << std::setw(3) << b.at(x,y);
        }
        os << std::endl;
    }
    return os;
}
