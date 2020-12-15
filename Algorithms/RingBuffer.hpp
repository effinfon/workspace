#ifndef RINGBUFFER_HPP_INCLUDED
#define RINGBUFFER_HPP_INCLUDED

#include <iostream>

// template adjustable, with fixed available choices,
    // whether to use uint8_t ... uint64_t (?) or arbitrary int(...)
    // like in SQL => ~ variable-length coding / non 2^n which implies
    // bitstreams
// type generic templating
struct RingBuffer {
private:
    // resizable
    uint16_t size {0};  // I would like read-only access by the public and write-access by the private, without using a get function (!?)
                // OS support ?
    // generic
    // in-object vs out-of-object
    int * buffer {nullptr};   // array in-object vs pointer to a possibly "more dense"
        // memory space (for example, an array of ring buffers, with their metadata being in an array of such definitions as this)
    //int buffer2[size];    // this won't work as is; it needs template programming and it's cumbersome, so I won't do it; unfeasible

    // choice: LI overwritting or "rotation sense alternation" mechanisms
    uint16_t read {0};
    uint16_t write {0};
    bool empty {true};  // this needs to be done away with, or use a uint8_t for it (same thing though, it is "bits with little density"

    // choice of mechanism:
    bool allowOverwritting {true};

public:
    RingBuffer(){}    // init state already defined with the data ("per data initialization" vs "per object initialization" ?!)

        // a few things have to change if overwritting is allowed; if it isn't allowed, and the buffer is full
        // then new data will simply be discarded
    void enque(int item);
    void queue(int item);   // alias enque()
    int deque();

    // typical of all containers that are (?"FIFO/LIFO with state-change on next()"?)
    int peek();
    int how_many_left();

    bool is_full(); // not relevant for internal mechanism much; but, for small sizes, instead of storing bool, one might do (write - read) == (size - 1),
            // but it wouldn't help when the overwritting begins
    bool is_empty();

    // take into consideration what happens in the "dense memory"
    void resize(uint16_t new_size);

    void reset();

    void deallocate_buffer();
        // consider if there's a "not enough memory available" kind of error, and try to get
            // the maximum available size then; probably use a geometric scaling to probe (?)
            // on the other hand, there would be a minimum size which could practically work,
            // but a too small size would be useless, forcing further backtrack or ? program-internal
            // memory management would better help with the memory request
    void reallocate_buffer();
    void allocate_buffer();



    void verbose() {
        std::cout << "size: " << size << "\nbuffer address: " << buffer << "\nbuffer content: ";
        for(uint16_t i = 0; i < size; i++) std::cout << buffer[i] << " ";
        std::cout << "\nread index: " << read << "\nwrite index: " << write << "\nempty: " << ((empty)? "true" : "false") << "\n";
    }
};

int RingBuffer::deque()
{
    if(empty == false) {
        int temp;
        if(empty == false) {
            temp = buffer[read++];
            read %= 100;
        }

        if(write == read && empty == false)
            empty = true;

        return temp;
    } else { return 0; }
}

void RingBuffer::enque(int item)
{
    buffer[write++] = item;
    empty = false;
    write %= 100;
}
#endif // RINGBUFFER_HPP_INCLUDED
