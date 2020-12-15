#ifndef TYPEDARRAY_HPP_INCLUDED
#define TYPEDARRAY_HPP_INCLUDED

#include "Utilitary.hpp"

template<typename T>
struct Array {
RPD_ACCESS private:
    T* buffer {};
    count_type length {0};
    count_type capacity;
    count_type buffer_size {capacity * sizeof(T)};
    count_type total_size {sizeof(Array<T>) + capacity * sizeof(T)};
    bool sorted {true};

public:
    explicit Array<T> (count_type capacity) : capacity(capacity) {
        buffer = new T[capacity];
    }

    void reallocate(count_type capacity) {
        if(capacity > length) {
            T* new_buffer = new T[capacity];
            for(count_type idx = 0; idx < length; idx++)
                new_buffer[idx] = buffer[idx];

            delete[] buffer;    // source of "un-intendence" errors / bugs! delete vs delete[]
        } else { }  // lossy
    }

    void insert(T element) {
        buffer[length++] = element; // how to ensure that a hard-copy is made ?
        // if(T is pointer) { get to the integral type while maintaining the
            // "pointer structure", copy the integral type, apply the pointer
            // structure, done
    }

    void insert_sort(T element) {
        if(sorted) {
            count_type position_idx = search_position(element, this);
            shift_array(this, position_idx, +1);
            buffer[position_idx] = element;
            length++;
        } else { }  // undecidable
    }

public:
    void verbose() {
        std::cout << "buffer: " << buffer << "\nlength: " << length <<
                    "\ncapacity: " << capacity << "\nbuffer_size: " <<
                    buffer_size << "\ntotal_size: " << total_size <<
                    "\nsorted: " << ((sorted)? "true" : "false") <<
                    "\ncontent: ";
        for(count_type idx = 0; idx < length; idx++) {
            if(idx % 5 == 0) std::cout << "\n";

            std::cout << buffer[idx] << " ";
        }
    }
};

#endif // TYPEDARRAY_HPP_INCLUDED
