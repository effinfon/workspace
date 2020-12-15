#ifndef RAWARRAY_HPP_INCLUDED
#define RAWARRAY_HPP_INCLUDED

#define count_type uint32_t

template<typename T>    // imperfect shift type and logic
void shift_right(T* array, count_type length, count_type position, count_type shift) {
    T temp = array[position];
    // ...
}

// idem shift_left


template<typename T>
bool equal_arrays(T** arrays, count_type number_of_arrays, count_type* array_sizes) {
    // optimizing for whether to use (-) or (+) -> number of cycles, op efficiency, and even energy consumption (?!)
    for(count_type idx_sizes {1}; idx_sizes < number_of_arrays; idx_sizes++) {
        if(!(array_sizes[idx_sizes] == array_sizes[idx_sizes - 1])) return false;
    }
    // the plurals and singulars seem to be all over the place / inconsistent; also, the "number_of_??" is rather long,
        // but it is rather "clear", right ?
    // here I used the opposite (-) and (+) pattern
    for(count_type idx_array {0}; idx_array < number_of_arrays - 1; idx_array++) {
        for(count_type idx_element {0}; idx_element < array_sizes[0]; idx_element++) {
            if(!(arrays[idx_array][idx_element] == arrays[idx_array + 1][idx_element])) return false;
        }
    }

    return true;
}
#endif // RAWARRAY_HPP_INCLUDED
