#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <vector>
#include <stdexcept>

// Simple panel to simply display images
// Cycle through image on user click, do the callback when
// one cycle is finished.
class HelpPanel : public Fl_Box {
private:
    // The index of the current image and a list of images
    int current_image;
    std::vector<Fl_Image*> images;
public:
    HelpPanel(int x, int y, int w, int h, std::vector<Fl_Image*> images)
        : Fl_Box(x, y, w, h),
        images(images) {
            // Set the image to be the first one. It's an error to pass
            // in an empty images vector.
            reset();
        }

    // Handle event
    int handle(int event);

    // Reset to the first image
    void reset();
};
