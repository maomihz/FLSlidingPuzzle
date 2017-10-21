#include <iostream>
#include "board.h"
#include <ctime>
#include <cstdlib>

using namespace SPuzzle;

int main() {
    srand(time(0));
    Board b(4);
    b.shuffle();
    std::cout << b << std::endl;
    char dir;
    while (std::cin >> dir) {
        switch(dir) {
        case 'w':
            b.up();
            break;
        case 'a':
            b.left();
            break;
        case 's':
            b.down();
            break;
        case 'd':
            b.right();
            break;
        }
        std::cout << b << std::endl;
        std::cout << (b.solvable() ? "Yes" : "No") << std::endl;
    }
}
