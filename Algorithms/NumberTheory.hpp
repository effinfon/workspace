#ifndef NUMBERTHEORY_HPP_INCLUDED
#define NUMBERTHEORY_HPP_INCLUDED

#include <iostream>

struct Float2 {
    float x {};
    float y {};

    Float2(float x, float y) : x(x), y(y) {}
};

struct Uint32_t2 {
    uint32_t x {};
    uint32_t y {};

    Uint32_t2() : x(0), y(0) {} // (!!?) there should be "local and global" syntax (!?) for
        // "just allocate, do not initialize", for "default constructor initialization", for "explicit initialization", etc.
    Uint32_t2(uint32_t x, uint32_t y) : x(x), y(y) {}
};

// what this does is to decompose $value into two numbers that are
    // "rather close" (the sum of their squares is minimal) with the
    // property that their product is equal to $value (basically, the
    // pair of numbers closest to the square root of $value, that are
    // factors of $value and $x * $y = $value
// assumed: value > 0

Uint32_t2 DecomposeIntoWidthAndHeight_v1(uint32_t value);   // alias: ~ "RectangleDecomposition" -> "SqaureDecomposable", "CubeDecomposable", "ParallelipipedDecomposition", etc.

#endif // NUMBERTHEORY_HPP_INCLUDED
