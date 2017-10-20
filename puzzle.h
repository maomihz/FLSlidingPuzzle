
namespace SPuzzle {

    struct Point {
        int x, y;
        // Constructor
        Point(int x = 0, int y = 0) : x(x), y(y) {}
        Point& operator+=(const Point a);
        Point& operator-=(const Point a);
        Point& operator=(const Point a);
    };

    const int UP = 0;
    const int DOWN = 1;
    const int LEFT = 2;
    const int RIGHT = 3;

    const Point DIRECTIONS[] = {
        Point(0, -1),   // Up
        Point(0, 1),    // Down
        Point(-1, 0),   // Left
        Point(1, 0)     // Right
    };

    class Board {
    private:
        int board[];   // The array used to hold the tiles
        int size;      // The size of the board
        int len;       // The length of the array used
        int space;     // The index of empty space

        int repr(Point p) const;          // Convert a point to index
        Point to_point(int repr) const;   // Convert an index to a point

        void swap(Point x, Point y);      // Swap two location
        bool valid(Point p) const;        // Check if the point is valid
        bool solvable() const;            // Check if the board is solvable

    public:
        Board(int size = 4);              // Constructor
        void shuffle();                   // Shuffle the board
        void move(int dir);               // Move in one direction
        bool can_move(int dir) const;     // Can move or not
        int at(Point p) const;

        Point space_pos() const;
        void reset();


    };

    class Game {
    private:
    public:
    };

};
