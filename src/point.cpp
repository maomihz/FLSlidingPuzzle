#include "point.h"

using namespace SPuzzle;
// ======= Constructors ========

Point::Point() :
    Point(0,0) {}


Point::Point(const int x, const int y) :
    x(x), y(y) {}


Point::Point(const Point& p) :
    Point(p.x, p.y) {}


// Point Addition & Subtraction operations
Point& Point::operator+=(const Point a) {
    x += a.x;
    y += a.y;
    return *this;
}

Point& Point::operator-=(const Point a) {
    x -= a.x;
    y -= a.y;
    return (*this);
}




Point Point::operator+(const Point a) const {
    return Point(x + a.x, y + a.y);
}

Point Point::operator-(const Point a) const {
    return Point(x - a.x, y - a.y);
}





// Point copy operator
Point& Point::operator=(const Point a) {
    x = a.x;
    y = a.y;
    return (*this);
}




// Point comparison operator
bool Point::operator==(const Point a) const {
    return x == a.x && y == a.y;
}

bool Point::operator!=(const Point a) const {
    return !((*this) == a);
}


std::ostream& operator<<(std::ostream& os, SPuzzle::Point p) {
    os << "(" << p.x << "," << p.y << ")";
    return os;
}
