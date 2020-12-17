#include "NumberTheory.hpp"

Uint32_t2 DecomposeIntoWidthAndHeight_v1(uint32_t value) {
    Uint32_t2 result {};
    uint64_t square_sum {0b1111111111111111111111111111111111111111111111111111111111111111};

    for(uint32_t idx {1}; idx * idx <= value; idx++) {
        if((value % idx) == 0) {
            /* register */ uint32_t idx_temp = value / idx;
            if( /* register annonymous */ (idx * idx + idx_temp * idx_temp) < square_sum) {
                square_sum = idx * idx + idx_temp * idx_temp;
                result.x = idx;
                result.y = idx_temp;
            }
        }
    }

    return result;
}
