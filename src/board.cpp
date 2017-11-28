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
    len_(size * size)
{
    board = new int[len_];  // Initialize to a long array
    for (int i = 0; i < len_; ++i) {
        board[i] = 0;
    }
}

// Copy constructor
Board::Board(const Board &another) : Board(another.size()) {
    (*this) = another;
}

// Destructor
Board::~Board() {
    delete [] board;
}

// Assignment Operator
Board& Board::operator=(const Board &another) {
    for (int i = 0; i < len(); ++i) {
        at(i) = another.at(i);
    }
    return *this;
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
