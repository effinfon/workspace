#ifndef COLLECTIONTYPES_HPP_INCLUDED
#define COLLECTIONTYPES_HPP_INCLUDED

/// TD
/*
    dynamically re-allocating array
    linked list
*/
/*
    monitoring tools for size and performance and etc. (*?!) <e.g.> how much of a linked list is data and how much is related to its structure (*?), etc.
*/

template<typename T>
struct DynamicArray {
    uint8_t scalar {};
    uint32_t capacity {};
    uint32_t cardinal {0};
    T* heap_allocated {nullptr};

    DynamicArray() : capacity(1024), scalar(2) {}
    DynamicArray(uint32_t capacity, uint8_t scalar = 2) : capacity(capacity), scalar(scalar) {
        heap_allocated = new T[capacity];
        for(uint32_t idx {0}; idx < capacity; idx++) {
            heap_allocated[idx] = T();
        }
    }

    T& operator [] (uint32_t index) {
        if(index < cardinal)
            return heap_allocated[index];
        else {
            T none {};
            return none; // isn't this an lvalue ? so how do you return a reference to it... temporary reference ?
        }
    }

    void reallocate() {
        uint32_t new_capacity = capacity * scalar;
        T* new_heap_allocated = new T[new_capacity];

        for(uint32_t idx {0}; idx < cardinal; idx++) {
            new_heap_allocated[idx] = heap_allocated[idx];
        }

        new_capacity = capacity;
        delete[] heap_allocated;
        heap_allocated = new_heap_allocated;
    }

    void operator += (T new_element) {
        if(capacity == cardinal) {
            reallocate();   // maybe I should also be able to decide here how much to reallocate with (*?)
                        // yes, if the position from which reallocate() is called has such knowledge or is
                        // cheap to obtain (!?)
        }

        heap_allocated[cardinal++] = new_element;   // (*?) how to ensure hard copy ? type traits, template progarmming ... (?)
                    // somehow check if T is a pointer type, then its internal structure, etc.
    }

    void operator -- () {
        heap_allocated[--cardinal] = T();
    }

    void verbose() {
        fprintf(stdout, "cardinal: %u, capacity: %u\n", cardinal, capacity);

        for(uint32_t idx {0}; idx < cardinal; idx++) {
            fprintf(stdout, "%lf ", heap_allocated[idx]);
        }
    }
};
#endif // COLLECTIONTYPES_HPP_INCLUDED
