#ifndef BITMAP_HPP_INCLUDED
#define BITMAP_HPP_INCLUDED

struct Bitmap {
    uint32_t width {};
    uint32_t height {};

    uint8_t* red {new uint8_t[width * height]}; // layer by layer, cache optimized
    uint8_t* green {new uint8_t[width * height]};
    uint8_t* blue {new uint8_t[width * height]};

    uint8_t* all {new uint8_t[width * height * 3]}; // whole pixel, cache optimized

    // (!?) need a method to propagate whatever change happens in either mode, to affect
        // the other mode of storage as well; thus, ~ "(data) integrity" (*?)

    // void operator = [] -> would need something like defining an operator of
        // assignment = that is called onto an element, through the index [] operator (*?)
    // having a function "set(enum color, index, value)" would work, but it's a too big
        // syntactic complexity involved for every use

    Bitmap(uint32_t width, uint32_t height) : width(width), height(height) {
        delete[] red;
        delete[] green;
        delete[] blue;
        delete[] all;

        red = new uint8_t[width * height];
        green = new uint8_t[width * height];
        blue = new uint8_t[width * height];
        all = new uint8_t[width * height * 3];
    }

    ~Bitmap() {
        delete[] red;
        delete[] green;
        delete[] blue;
        delete[] all;
    }

    void update_colors() {
        for(uint32_t i {0}, j {0}; i < this->height; j++) {
            if(j == this->width) { j = -1; i++; continue; }

            red[i * this->width + j] = all[(i * this->width + j) * 3 + 0];
            green[i * this->width + j] = all[(i * this->width + j) * 3 + 1];
            blue[i * this->width + j] = all[(i * this->width + j) * 3 + 2];
        }
    }

    void update_all() {
        for(uint32_t i {0}, j {0}; i < this->height; j++) {
            if(j == this->width) { j = -1; i++; continue; }

            all[(i * this->width + j) * 3 + 0] = red[i * this->width + j];
            all[(i * this->width + j) * 3 + 1] = green[i * this->width + j];
            all[(i * this->width + j) * 3 + 2] = blue[i * this->width + j];
        }
    }
};

#endif // BITMAP_HPP_INCLUDED
