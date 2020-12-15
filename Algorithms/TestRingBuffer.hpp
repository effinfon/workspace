#ifndef TESTRINGBUFFER_HPP_INCLUDED
#define TESTRINGBUFFER_HPP_INCLUDED

#include "RingBuffer.hpp"

void test() {
    std::cout << "Starting tests.\n";
    RingBuffer ring;
    // test 1: queue and dequeue
    std::cout << "Test1: ";
    for(int i = 0; i < 100; i++) {
        ring.enque(i);
        std::cout << ring.deque() << " ";
    } std::cout << "\n";

    // test 2: "go over" / "exceed" the buffer
    std::cout << "Test2: ";
    for(int i = 0; i < 200; i++) {
        ring.enque(i);
    }
    for(int i = 0; i < 100; i++) {
        std::cout << ring.deque() << " ";
    } std::cout << "\n";

    // test 3: a mixture of queue-deque and "exceed" the buffer
    std::cout << "Test3: ";
    for(int i = 0; i < 50; i++) {
        ring.enque(i);
        std::cout << ring.deque() << " ";
    }
    for(int i = 50; i < 350; i++) {
        ring.enque(i);
    }
    for(int i = 0; i < 100; i++) {
        std::cout << ring.deque() << " ";
    } std::cout << "\n";
}


#endif // TESTRINGBUFFER_HPP_INCLUDED
