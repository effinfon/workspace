#ifndef COUNTPROBLEMS_HPP_INCLUDED
#define COUNTPROBLEMS_HPP_INCLUDED

#include <string>

/// TD
/*
    how many Fibonacci numbers in the uint16_t, uint32_t and uint64_t; basically, how many
        Fibonnaci in a n bit uint (*?); produce an array of them
    how many primes in n bit uint ? produce an array of them; try to compress that array
    how much space does it take to allocate all the possible states of uint16_t, of
        uint32_t and of uint64_t (*?), while optimizing the type selected for each (*?), or
        maybe using VLC if it helps, but I'd rather guess that a bitstream method is
        needed for that (with a separator) and even then would not do better than "having the
        compile-time, structural knowledge" about which type is stored where and how long it is
    arbitrary length uint type (!?)
*/

struct ArbUint {

};

uint64_t fibonacci(uint64_t uint_bits) {
    if(uint_bits == 32) {
        uint32_t count {1};
        uint32_t a {0}, b {1};
        while(a + b >= b) {
            // count a + b; the annoying thing is that 1 gets counted twice, unless
                // $count's initialization is carefully done
            b = a + b;
            a = b - a;

            count++;
        }
    } else if (uint_bits == 64) {
        uint64_t count {1};
        uint64_t a {0}, b {1};
        while(a + b >= b) {
            // count a + b; the annoying thing is that 1 gets counted twice, unless
                // $count's initialization is carefully done
            count++;
        }
    }
}

// (!!?) some algorithms can be executed and directly turned into their output as pre-compute,
    // especially if the algorithm itself occupies more space than the result (!?)
uint32_t u32_squares() {
    uint32_t count {0};
    for(uint32_t idx {1}; idx * idx >= idx; idx++, count++) ;
    return count;
}
uint64_t u64_squares() {
    uint64_t count {0};
    for(uint64_t idx {1}; idx * idx >= idx; idx++, count++) ;    // the point of this is to stop on the first overflow (!?)
    return count;
}   // so this could be turned into "static uint64_t u64_squares {...}"
uint64_t u64_cubes() {
    uint64_t count {0};
    for(uint64_t idx {1}; idx * idx * idx >= idx; idx++, count++) ;
    return count;
}
#endif // COUNTPROBLEMS_HPP_INCLUDED
