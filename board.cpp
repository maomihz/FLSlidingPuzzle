#include "puzzle.h"
#include <stdexcept>

// Initialize a board with a specified size
SPuzzle::Board::Board(int size) {
    // Board size should not be less than 3
    if (size < 3)
        throw std::runtime_error("Puzzle size should not be less than 4");

    // Calculate the length of the array
    len = size * size;
    board = new int[len];

    // Assign the numbers in order, except the last one
    for (int i = 0; i < len - 1; ++i) {
        board[i] = i;
    }
    board[len - 1] = 0;  // Set the last one to zero
    space = len - 1;     // Set the space location to the last one
}

void SPuzzle::Board::move(int dir) {

}
