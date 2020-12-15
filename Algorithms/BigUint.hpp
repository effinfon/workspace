#ifndef BIGUINT_HPP_INCLUDED
#define BIGUINT_HPP_INCLUDED

#include <limits.h>

typedef unsigned int uint128_t __attribute__((mode(TI)));

struct BigUint {
    uint64_t* lsb_block {};
    uint64_t length_lsb {};

    // init from very large, in-code numbers (?!), will likely require using strings as intermediaries
    // as I do not know the intricacies of the compiler
    BigUint(uint64_t* lsb_first, uint64_t length) {
        length_lsb = length;
        lsb_block = new uint64_t[length_lsb];

        for(uint64_t idx = 0; idx < length_lsb; idx++) {
            lsb_block[idx] = lsb_first[idx];    // hard-copy
        }
    }

    void operator = (BigUint& a) {
        this->lsb_block = a.lsb_block;
        this->length_lsb = a.length_lsb;
    }

    // index operators return reference (?!) <e.g. usage> counter[idx]++;
    uint64_t& operator [] (uint64_t index) {
        return lsb_block[index];
    }

    // the compiler needs to understand the difference between an operator that operates on $this
    // and a binary operator that needs to consider associativity (?!)
    /* static */ BigUint operator + (BigUint op /*, BigUint b */) {
        uint64_t idx {};

        // how about trying a re-aliasing (?); would using a ~ "dynamic reference"
            // actually make use of run-time support ?
/*
        if(this->length_lsb < op.length_lsb) {
            BigUint c = op;
            // seriously ?, $this is not an lvalue... wtf C++ ?
            // well, to some degree it makes sense in that it simplifies optimization and
            // interpretation and verification, but still...
            //this = &op;
            op = c;
        }
*/  // due to reasons, this method is postponed


        uint128_t temp = (*this)[idx] + op[idx++];  // notice that only the last index has a post++

//        if(temp > ULLONG_MAX)
    }
};


#endif // BIGUINT_HPP_INCLUDED
