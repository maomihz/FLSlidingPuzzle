#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/fl_draw.H>
#include "game.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

class GameBoard : Fl_Widget {
public:
    void draw() {

        fl_line_style(FL_SOLID, 8);
        fl_line(10, 5, 40, 5);
        fl_line(5, 10, 5, 60);
        fl_line(10, 65, 40, 65);
        fl_line(45, 10, 45, 20);
        fl_line(45, 50, 45, 60);


        fl_line(120, 55, 120, 105);
        fl_line(120, 50, 150, 50);
        fl_line(150, 55, 150, 105);
        fl_line(120, 70, 150, 70);

        fl_line(170, 50, 210, 50);
        fl_line(190, 50, 190, 105);
    }


    GameBoard(int x, int y, int w, int h, const char *label=0L) : Fl_Widget(x, y, w, h, label) {

    }
};

vector <Fl_Button *> boxes;
int main(int argc, char **argv) {
    Fl_Window *window = new Fl_Window(800, 600, "Sliding Puzzle");
    SPuzzle::Game g;
    // for(int i = 0; i < 4; ++i) {
    //     for(int j = 0; j < 4; ++j) {
    //         Fl_Button *b = new Fl_Button(i * 100, j * 100,100,100,"bao");
    //         boxes.push_back(b);
    //     }
    // }

    GameBoard *bo = new GameBoard(0,0,100,100);

    window->end();
    window->show(argc, argv);
    while(Fl::wait()) {
        // for (int i = 0; i < 16; ++i) {
        //     string s = to_string(g.board()->at(i));
        //     boxes[i] -> label(const_cast<char*> (s.c_str()));
        // }
        // boxes[0] -> label(to_string(g.board()->at(0)).c_str());
        // boxes[1] -> label(to_string(g.board()->at(1)).c_str());
        // boxes[2] -> label(to_string(g.board()->at(2)).c_str());
        // boxes[3] -> label(to_string(g.board()->at(3)).c_str());
        // boxes[4] -> label(to_string(g.board()->at(4)).c_str());
        // boxes[5] -> label(to_string(g.board()->at(5)).c_str());
        // boxes[6] -> label(to_string(g.board()->at(6)).c_str());
        // boxes[7] -> label(to_string(g.board()->at(7)).c_str());
        // boxes[8] -> label(to_string(g.board()->at(8)).c_str());
        // boxes[9] -> label(to_string(g.board()->at(9)).c_str());
        // boxes[10] -> label(to_string(g.board()->at(10)).c_str());
        // boxes[11] -> label(to_string(g.board()->at(11)).c_str());
        // boxes[12] -> label(to_string(g.board()->at(12)).c_str());
        // boxes[13] -> label(to_string(g.board()->at(13)).c_str());
        // boxes[14] -> label(to_string(g.board()->at(14)).c_str());
        // boxes[15] -> label(to_string(g.board()->at(15)).c_str());
        // for (int a = 1; a <= 3; ++a) {
        //     std::stringstream ssb;
        //     ssb << a << "bnr" << rand();
        //     cout << "B:" << ssb.str().c_str() << endl;
        //     boxes[a] -> label(ssb.str().c_str());
        //     cout << "B2:" << boxes[a]->label() << endl;
        // }
        // for (int a = 1; a <= 3; ++a) {
        //     cout << boxes[a] -> label() << endl;
        // }
    }
}
