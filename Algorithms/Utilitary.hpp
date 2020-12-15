#ifndef UTILITARY_HPP_INCLUDED
#define UTILITARY_HPP_INCLUDED

#include "TypeMacro.hpp"

// algorithmic configuration
#define LINEAR_SEARCH
#define BINARY_SEARCH
#define MULTI_THREADED_SEARCH
    #ifdef MULTI_THREADED_SEARCH
        #include <pthread.h>
        // can I add a library to the project from code ?
    #endif

template<typename T>
count_type search_position(T element, Array<T> array) {
    count_type estimated_array_size = 1;    // (!!) could use a different search algorithm based on this
    bool asceding {true};   // current default

    count_type idx = 0;
#ifdef LINEAR_SEARCH
    while (element < array[idx]) idx++;

    return idx;
#endif

#ifdef BINARY_SEARCH
    // ...

    return idx;
#endif

#ifdef MULTI_THREADED_SEARCH
    // fork()   // needs a function defined for the "distributed node" -> defines its state, its search-space, etc.
                // should also
    // join()
    return idx;
#endif
}

shift_array(this, position_idx, +1);


#endif // UTILITARY_HPP_INCLUDED
