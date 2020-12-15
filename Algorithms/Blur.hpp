#ifndef BLUR_HPP_INCLUDED
#define BLUR_HPP_INCLUDED

#include "Bitmap.hpp"

void downsample_border_by_sliding_3x3(Bitmap& bitmap) {
    if(bitmap.width >= 3 && bitmap.height >= 3) {
        uint32_t i {0};
        uint32_t j {0};
        Bitmap downsampled_bitmap {bitmap.width - 2, bitmap.height - 2};


    }
}
void average_sliding_3x3(Bitmap& bitmap) {
    if(bitmap.width >= 3 && bitmap.height >= 3) {
        uint32_t i {0};
        uint32_t j {0};


    }
}
void average_block_3x3(Bitmap& bitmap) {

}
#endif // BLUR_HPP_INCLUDED
