#include <iostream>
#pragma once

namespace SPuzzle {
    // ===== Coordinate System Uses Point =====
    struct Point {
        int x;
        int y;
        // Constructors
        Point();
        Point(const int x, const int y);
        Point(const Point& p);

        // Operators
        Point& operator+=(const Point a);
        Point& operator-=(const Point a);

        Point operator+(const Point a) const;
        Point operator-(const Point a) const;

        Point& operator=(const Point a);

        bool operator==(const Point a) const;
        bool operator!=(const Point a) const;
    };
};

std::ostream& operator<<(std::ostream& os, SPuzzle::Point p);
