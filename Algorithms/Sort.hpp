#ifndef SORT_HPP_INCLUDED
#define SORT_HPP_INCLUDED

#ifdef count_type
#undef count_type
#endif
#define count_type uint32_t
#define c_t count_type


/// TD
/*
    set default cmp function pointer and default ascending order bool
*/

int compare_int(int& a, int& b) {
    if(a < b) { return -1; }
    else if(a > b) { return 1; }
    else { return 0; }
}


/// Sorting properties
    // now, different algorithms in their "default" variant do not have or have some sorting properties;
    // so this is about producing their different variants based on what properties are desired
    // from them and can be easily obtained from them
// <e.g. Sorting Properties> stability, fastest, external / internal, large file / small file, in-place / allocate space,

/// Helper

template<typename T>
void swap(T* array, count_type idx_a, count_type idx_b) {
    T storage = array[idx_a]; // ensures hard-copy ?
    array[idx_a] = array[idx_b];
    array[idx_b] = storage;
}

/// Single Objective Sorting

template<typename T>
void selection_sort(T* array, count_type length, int (*cmp)(T&, T&), bool ascending_ordering) {
    if(ascending_ordering) {
        for(count_type master {length}; master > 1; master--) { // (?"master" / "control"?)
            T monitor {array[0]};
            count_type origin_idx {0};

            for(count_type idx {1}; idx < master; idx++) {
                if(cmp(array[idx], monitor) == +1 /* -1 */) {    // the inversion of this will also produce the inversion in logic ? no, it won't
                                                        // but it produces an interesting symmetry where the max are to the left and the
                                                        // min to the right, ordered symmetrically
                    monitor = array[idx];
                    origin_idx = idx;
                }
            }

            swap<T>(array, origin_idx, master - 1);
        }

    }
}

template<typename T>
void insertion_sort(T* array, count_type length, int (*cmp)(T& a, T& b), bool ascending_ordering) {
    if(ascending_ordering) {    // this should be done away with and introduced into the arithmetic ? (at least it might result in less code)
        for(count_type idx {1}; idx < length; idx++) {
            count_type scope_idx {idx};
            while(scope_idx > 0 && cmp(array[scope_idx], array[scope_idx - 1]) == -1)    // this can make use of sentinelling, but
                                        //it is liekly counter-performant in short-runs; and then again, there's the cache-line
            {
                swap<T>(array, scope_idx, scope_idx - 1);
                scope_idx--;
            }
        }
    }
}

template<typename T>
void bubble_sort(T* array, count_type length, int (*cmp)(T&, T&), bool ascending_ordering) {
    if(ascending_ordering) {
        for(count_type idx_1 /* idx_outer; or reverse the order of the counting so that the deepest one is idx_1 */ {length}; idx_1 > 0; idx_1--) {
            T monitor {array[0]};
            count_type origin_idx {0};

            for(count_type idx_2 {1}; idx_2 < idx_1; idx_2++) {
                if(cmp(monitor, array[idx_2]) == -1) {
                    monitor = array[idx_2];
                    origin_idx = idx_2;
                }
            }

            swap<T>(array, idx_1 - 1, origin_idx);
        }
    }
}
#endif // SORT_HPP_INCLUDED
