#ifndef FILELOADERBMP_HPP_INCLUDED
#define FILELOADERBMP_HPP_INCLUDED

#include <GL/glew.h>
#include <stdio.h>

typedef unsigned char uchar8_t;

//GLuint loadBMP_custom(const char * imagepath);
// GLuint image = loadBMP_custom("./mytexture.bmp");

struct Bitmap_v2 {
    uchar8_t header[54] {};
    uint32_t width {0};
    uint32_t height {0};
    uchar8_t* data {nullptr};

    Bitmap_v2() {}  // I hope this uses the above init values
    Bitmap_v2(uint32_t width, uint32_t height, uchar8_t* data) :
        header{}, width(width), height(height), data(data) {}
    Bitmap_v2(uchar8_t header[54], uint32_t width, uint32_t height, uchar8_t* data) :
        header{}, width(width), height(height), data(data) {
        for(uint8_t idx{0}; idx < 54; idx++) {
            this->header[idx] = header[idx];
        }
    }
};

Bitmap_v2 LoadBMP(const char * imagepath);

#endif // FILELOADERBMP_HPP_INCLUDED
