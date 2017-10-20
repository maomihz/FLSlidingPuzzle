#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input.H>
#include <cstdlib>
#include <ctime>


Fl_Check_Button *cbtn;
Fl_Box *box;
Fl_Input *ipt;

void btncall(Fl_Widget* w, void* arg) {
    if (cbtn->value()) {
        w->label("bnr!");
    } else {
        w->label("smg!");
    }
    box->color(fl_rgb_color(rand() % 255, rand() % 255, rand() % 255));
    box->redraw();
}

void chkcall(Fl_Widget* w, void* arg) {
    switch(rand() % 3) {
    case 0:
        box->label("yayayaya");
        break;
    case 1:
        box->label("bbbnr!!!");
        break;
    default:
        box->label(ipt->value());
    }
}
int main(int argc, char **argv) {
    srand(time(0));
    Fl_Window *window = new Fl_Window(800, 600, "FLTK Testing");
    box = new Fl_Box(20,40,300,100,"Hello, World!");
    Fl_Button *btn = new Fl_Button(360, 60, 100, 50, "Test");
    btn->callback(btncall);
    cbtn = new Fl_Check_Button(500, 60, 300, 50, "This is a check button");
    cbtn->callback(chkcall);
    ipt = new Fl_Input(500, 180, 300, 50, "This is a check button");
    ipt->value("Type something here!");
    box->box(FL_UP_BOX);
    box->labelsize(30);
    box->labeltype(FL_SHADOW_LABEL);
    window->end();
    window->show(argc, argv);
    int b = 0;

    return Fl::run();
}
