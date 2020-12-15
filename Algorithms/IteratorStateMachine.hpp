#ifndef ITERATORSTATEMACHINE_HPP_INCLUDED
#define ITERATORSTATEMACHINE_HPP_INCLUDED

template<typename T>
struct MatrixIterator {
    T* array {nullptr};   // how do I dynamically cast an array pointer to a 2Dim array (?), to be able to use the [][] syntax
    uint32_t length1 {0};
    uint32_t length2 {0};
    uint32_t length {length1 * length2};

    enum Mode { // I really want more descriptive names, with punctuation (!?)
                // I'd also want diagrams which visually describe the pattern (!?), and maybe even algebraic expressions to describe the indices sequence (*?), etc.
        Spiral_clockwise_inwards,
        Spiral_anticlockwise_inwards,
        Spiral_clockwise_outwards,
        Spiral_anticlockwise_outwards,
        Linear_left_right_up_down,
        Linear_right_left_up_down,
        Linear_right_left_down_up,
        Linear_left_right_up_down,
        Linear_up_down_left_right,
        Linear_up_down_right_left,
        Diagonal_Primary,
        Diagonal_Secondary,
        Fibonacci_modulo,
        Power_of_2_modulo,
        Prime_indices,
        Even_first_odd_after,
        Odd_first_even_after,
        Square_2x2,
        Square_3x3,
        Upper_triangle_Primary_diagonal_Lower_triangle,
        Upper_triangle_Secondary_diagonal_Lower_triangle,

    } mode {Linear_left_right_up_down};

    MatrixIterator() {}

    void SetMode(Mode mode) {
        this->mode = mode;
    }

    void Next() {
        switch(mode) {
        case Spiral_clockwise_inwards:
            break;
        default:
            break;
        }
    }
};

#endif // ITERATORSTATEMACHINE_HPP_INCLUDED
