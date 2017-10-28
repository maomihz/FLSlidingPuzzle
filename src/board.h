#include "point.h"
#include <string>
#include <iostream>
#include <iomanip>

#pragma once

namespace SPuzzle {


    // ====== the Board class used to represent a game board ======
    class Board {
    private:
        // The main storage array, one dimentional.
        int* board;

        // Some variables associated with the array
        // for easier access.
        int size_;      // The size of the board
        int len_;       // The length of the array, equals to size squared


    public:
        Board(int size = 4);              // Constructor, defaults to size 4
        Board(Board &another);            // Copy constructor
        ~Board();                         // Destructor

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

        int& at(int x, int y) const;      // Content of a location using x,y
        int& at(int repr) const;          // Content of a location using index
        int& at(Point p) const;           // Content of a location using Point

        std::string at_str(int x, int y) const;
        std::string at_str(int repr) const;
        std::string at_str(Point p) const;


        // Several accesser functions
        int size() const {return size_;}
        int len() const {return len_;}

    };

};
std::ostream& operator<<(std::ostream& os, const SPuzzle::Board& b);
