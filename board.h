#include "point.h"

#pragma once

namespace SPuzzle {
    // ====== the Board class used to represent a game board ======
    class Board {
    private:
        // The main storage array, one dimentional.
        int* board;

        // Some variables associated with the array
        // for easier access.
        int size;      // The size of the board
        int len;       // The length of the array, equals to size squared
        Point last;    // The last point in the board
        Point space;   // The index of empty space

    	// The main storage uses a one-dimensional array, therefore
        // there is two different representation of the coordinates.
        // These functions do the conversion between a point and a
        // internal (index) representation of a coordinate.
        //
        // Note that the functions in this class usually takes three
        // different forms, you can pass either x, y or a Point object
        // or a internal (index) representation to express the coordinate.
        int repr(int x, int y) const;     // Convert a point to index (x, y)
        int repr(Point p) const;          // Convert a point to index (Point)
        Point to_point(int repr) const;   // Convert an index to a Point

    	// helper functions that are not intended to expose to the public/
        // Notice that they all take three different forms to express coordinate
        void swap(int x1, int y1,
                  int x2, int y2);       // Swap two location using x, y
        void swap(int repra, int reprb); // Swap two location using index
        void swap(Point a, Point b);     // Swap two location using points
        bool valid(int x, int y) const;  // Check if a point is valid with x,y
        bool valid(int repr) const;      // Check if a point is valid with index
        bool valid(Point p) const;       // Check if a point is valid witn Point

    public:
        Board(int size = 4);              // Constructor, defaults to size 4

        int& at(int x, int y) const;      // Content of a location using x,y
        int& at(int repr) const;          // Content of a location using index
        int& at(Point p) const;           // Content of a location using Point

        bool can_move(int dir) const;     // Can move or not
        bool move(int dir);               // Move in one direction

        void reset();             // Reset board to initial location
        void shuffle();           // Shuffle the board
        bool win() const;         // Check if the board is in winning position.
                                  // The initial position is always the winning
                                  // postition.


        bool solvable() const;    // Check if the board is solvable

    };
};