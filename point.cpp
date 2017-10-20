#include "puzzle.h"

SPuzzle::Point& SPuzzle::Point::operator+=(const Point a) {
    x += a.x;
    y += a.y;
    return (*this);
}

SPuzzle::Point& SPuzzle::Point::operator-=(const Point a) {
    x -= a.x;
    y -= a.x;
    return (*this);
}

SPuzzle::Point& SPuzzle::Point::operator=(const Point a) {
    x = a.x;
    y = a.y;
    return (*this);
}
