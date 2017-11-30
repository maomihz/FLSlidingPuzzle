#include "HelpPanel.h"

int HelpPanel::handle(int event) {
    // Mouse click event
    if (event == FL_RELEASE) {
        try {
            image(images.at(++current_image));
            redraw();
        } catch (std::out_of_range e) {
            // If the cycle is over, then start from the first image again
            reset();
            redraw();
            // Do a callback when a new cycle begins
            do_callback();
        }
    }
    return Fl_Box::handle(event);
}

int HelpPanel::reset() {
    current_image = 0;
    image(images.at(0));
}
