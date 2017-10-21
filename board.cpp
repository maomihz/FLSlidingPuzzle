#include "puzzle.h"
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using namespace SPuzzle;

// ========================================
// ------------ Constructors --------------
// ========================================

// Initialize a board with a specified size
Board::Board(int size) :
    size(size),
    len(size * size),
    last(Point(size - 1, size - 1))
{
    // Board size should not be less than 3
    if (size < 3)
         throw std::runtime_error("Puzzle size should not be less than 4");

    // Initialize the board to a long array
    board = new int[len];

	// Reset to the initial state
    reset();
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
    Point next = space + DIRECTIONS[dir];
    return valid(next);
}


// To make an actual move. If the direction is not moveable
// then the function would do nothing and return false.
// If a move is successfully made the function returns true.
bool Board::move(int dir) {
    // Still check validity first
    if (!can_move(dir)) return false;

    Point next = DIRECTIONS[dir] + space;
    swap(space, next);
    space = next;
    return true;
}





// Resets the board to the initial state.
// The initial state is the winning state.
void Board::reset() {
    // Assign the numbers in order, except the last one
    for (int i = 0; i < repr(last); ++i) {
        at(i) = i + 1;
    }
    at(last) = 0;    // Set the last one to zero
    space = last;    // Set the space location to the last one
}



// Shuffle the board
// The shuffle function don't care if the board is
// in the initial state or not
void Board::shuffle() {
    // Restore the location of empty space first
    swap(space, last);
    space = last;

    // Trust the rand() function and do the shuffling
    // Skip the last location
    for (int i = 0; i < repr(last); ++i) {
        // It is valid if the chosen point is itself.
        int to_swap = rand() % (repr(last) - i) + i;
        swap(i, to_swap);
    }
    // ****==== TODO: Check if solvable or not ====****
}




// Check whether the layout is equal to the winning position.
bool Board::win() const {
    // Check everything except the last one
    // If everything except the last one is equal to the
    // winning position then the last one must be zero
    for (int i = 0; i < size * size - 1; ++i) {
        if (at(i) != i) {
            return false;
        }
    }
    // Otherwise, return true
    return true;
}



bool Board::solvable() const {
    return false;
}



// ================================================
// ------- Helper Functions implementations -------
// ================================================
// Convert the "internal" representation to point or back
int Board::repr(int x, int y) const {
    return x * size + y;
}
int Board::repr(Point p) const {
    return repr(p.x, p.y);
}
Point Board::to_point(int repr) const {
    return Point(repr / size, repr % size);
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
    return (x >= 0 && x < size && y >= 0 && y < size);
}
bool Board::valid(int repr) const {
    return valid(to_point(repr));
}
bool Board::valid(Point p) const {
    return valid(p.x, p.y);
}
