#include "point.h"
#include "board.h"

namespace SPuzzle {
    // ===== Some constants ======
    // Constants to represent moving direction
    const int UP = 0;
    const int DOWN = 1;
    const int LEFT = 2;
    const int RIGHT = 3;

    // A map for constant to point. These points can be added to a existing
    // point to calculate the coordinate the point is moving to.
    const Point DIRECTIONS[] = {
        Point(0, -1),   // Up
        Point(0, 1),    // Down
        Point(-1, 0),   // Left
        Point(1, 0)     // Right
    };

};
