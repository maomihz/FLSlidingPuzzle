#include "point.h"
#include <string>
#include <iostream>
#include <iomanip>

#pragma once

namespace SPuzzle {
    // ===== Some constants ======
    // Constants to represent moving direction
    const int UP = 0;
    const int DOWN = 1;
    const int LEFT = 2;
    const int RIGHT = 3;

    // A map for constant to point. These points can be added to a existing
    // point to calculate the coordinate the point is moving to.
    // The direction is actually reversed because if you are moving up
    // then the space is moving down.
    const Point DIRECTIONS[] = {
        Point(0, 1),   // Up
        Point(0, -1),    // Down
        Point(1, 0),   // Left
        Point(-1, 0)     // Right
    };

    // ====== the Board class used to represent a game board ======
    class Board {
    private:
        // The main storage array, one dimentional.
        int* board;

        // Some variables associated with the array
        // for easier access.
        int size_;      // The size of the board
        int len_;       // The length of the array, equals to size squared
        Point last_;    // The last point in the board
        Point space_;   // The index of empty space

    	// The main storage uses a one-dimensional array, therefore
        // there is two different representation of the coordinates.
        // These functions do the conversion between a point and a
        // internal (index) representation of a coordinate.
        //
        // Note that the functions in this class usually takes three
        // different forms, you can pass either x, y or a Point object
        // or a internal (index) representation to express the coordinate.
        //
        // The board looks like this:
        // (0,0) (1,0) (2,0) (3,0)  ==>  0  1  2  3
        // (0,1) (1,1) (2,1) (3,1)  ==>  4  5  6  7
        // (0,2) (1,2) (2,2) (3,2)  ==>  8  9  10 11
        // (0,3) (1,3) (2,3) (3,3)  ==>  12 13 14 15
        // Therefore the conversion would be y * size + x
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
        Board(Board &another);            // Copy constructor
        ~Board();                         // Destructor

        int& at(int x, int y) const;      // Content of a location using x,y
        int& at(int repr) const;          // Content of a location using index
        int& at(Point p) const;           // Content of a location using Point

        std::string at_str(int x, int y) const;
        std::string at_str(int repr) const;
        std::string at_str(Point p) const;

        bool can_move(int dir) const;     // Can move or not
        bool move(int dir);               // Move in one direction

        void reset();             // Reset board to initial location
        void shuffle();           // Shuffle the board
        int correct_count() const;// Count the number of tiles that is in the
                                  // correct location. 0 <= n < len, not
                                  // including the space tile.
        bool win() const;         // Check if the board is in winning position.
                                  // The initial position is always the winning
                                  // postition.


        bool solvable() const;    // Check if the board is solvable

        // Several accesser functions
        int size() const {return size_;}
        int len() const {return len_;}
        Point last() const {return last_;}
        Point space() const {return space_;}

    };

};
std::ostream& operator<<(std::ostream& os, const SPuzzle::Board& b);
