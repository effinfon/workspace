#ifndef HASH_HPP_INCLUDED
#define HASH_HPP_INCLUDED

#include <iostream>
#include <iomanip>

#include <x86intrin.h>

#ifdef INTEL_INTRINSICS
#include <x86intrin.h>
#elif AMD_INTRINSICS
//#include <
#endif

/**  PSEUDOCODE SHA-1
Note 1: All variables are unsigned 32-bit quantities and wrap modulo 232 when calculating, except for
        ml, the message length, which is a 64-bit quantity, and
        hh, the message digest, which is a 160-bit quantity.
Note 2: All constants in this pseudo code are in big endian.
        Within each word, the most significant byte is stored in the leftmost byte position

Initialize variables:

h0 = 0x67452301
h1 = 0xEFCDAB89
h2 = 0x98BADCFE
h3 = 0x10325476
h4 = 0xC3D2E1F0

ml = message length in bits (always a multiple of the number of bits in a character).

Pre-processing:
append the bit '1' to the message e.g. by adding 0x80 if message length is a multiple of 8 bits.
append 0 ≤ k < 512 bits '0', such that the resulting message length in bits
   is congruent to −64 ≡ 448 (mod 512)
append ml, the original message length, as a 64-bit big-endian integer.
   Thus, the total length is a multiple of 512 bits.

Process the message in successive 512-bit chunks:
break message into 512-bit chunks
for each chunk
    break chunk into sixteen 32-bit big-endian words w[i], 0 ≤ i ≤ 15

    Message schedule: extend the sixteen 32-bit words into eighty 32-bit words:
    for i from 16 to 79
        Note 3: SHA-0 differs by not having this leftrotate.
        w[i] = (w[i-3] xor w[i-8] xor w[i-14] xor w[i-16]) leftrotate 1

    Initialize hash value for this chunk:
    a = h0
    b = h1
    c = h2
    d = h3
    e = h4

    Main loop:[3][58]
    for i from 0 to 79
        if 0 ≤ i ≤ 19 then
            f = (b and c) or ((not b) and d)
            k = 0x5A827999
        else if 20 ≤ i ≤ 39
            f = b xor c xor d
            k = 0x6ED9EBA1
        else if 40 ≤ i ≤ 59
            f = (b and c) or (b and d) or (c and d)
            k = 0x8F1BBCDC
        else if 60 ≤ i ≤ 79
            f = b xor c xor d
            k = 0xCA62C1D6

        temp = (a leftrotate 5) + f + e + k + w[i]
        e = d
        d = c
        c = b leftrotate 30
        b = a
        a = temp

    Add this chunk's hash to result so far:
    h0 = h0 + a
    h1 = h1 + b
    h2 = h2 + c
    h3 = h3 + d
    h4 = h4 + e

Produce the final hash value (big-endian) as a 160-bit number:
hh = (h0 leftshift 128) or (h1 leftshift 96) or (h2 leftshift 64) or (h3 leftshift 32) or h4
*/

namespace Utilitary {
    void InvertEndian() {}
    void InvertStartian() {}    // (*?) to me, "endian" doesn't make sense; it's more like "startian"; we are talking about the "lower address" here, right (?)

    struct LiteralValue{};
    void LSBStartian(LiteralValue value) {}
    void MSBStartian(LiteralValue value) {}

    // (!?) need to check for whether the CPU is Intel or AMD, then switch the macro definitions accordingly
/*  // Intel
#define _rotl(a,b)		__rold((a), (b))
#define _rotr(a,b)		__rord((a), (b))
*/
    uint32_t leftrotate(uint32_t number, uint8_t shifts) {
        return _rotl(number, shifts);
    }
};

namespace HashPlayground {

    struct Bitarray {
        // (*?) at this point, the representation is agnostic to the startian (?!)
        uint8_t* bits {nullptr};
        uint64_t count_bits {};

        struct Block512 {
            uint32_t block[16]; // (!?) this needs to be big-endian => (i) invert it and go as per the pseudo-code; (ii) invert the order of operations in the pseudocode,
                                // if the pseudocode is commutative (!?)

            // TODO: TO DO: TO-DO: not safe
            uint32_t& operator [] (uint8_t index) {
                return block[index];
            }
        };

        struct BlockContainer {
            Block512* blocks {nullptr};
            uint64_t count_blocks {0};

            // unsafe for now
            Block512& operator [] (uint64_t index) {
                return blocks[index];
            }
        };

        // (*?) I am rather confident that this is NOT the pre-processing I have to do though
        // (i) 0's to mod 8
        // (ii) 0x80 terminator
        // (iii) again 0's to 512 - 64 = 448  mod 512
        // (iv) append resultant length (of the "payload") as a "trailer" (terminology is ~ to Layer 2 packets (I think; I mean the MAC address packets)

        void Preprocess() {}

        BlockContainer BreakMessageIntoBlocks() {}
    };

    struct SHA160Bit {
        uint32_t hash[5] {};

        SHA160Bit(uint32_t* block_hashes) { // assumed to have length 5
        /*  // basically a concatenation of 5 * 32bit; for visualization, convert them to a hexadecimal string
            hh = (h0 leftshift 128) or (h1 leftshift 96) or (h2 leftshift 64) or (h3 leftshift 32) or h4
        */
            for(uint8_t idx {0}; idx < 5; idx++) {
                hash[idx] = block_hashes[idx];

                // verbose
                std::cout << std::setw(8) << std::setfill('0') << std::hex << std::uppercase << hash[idx];
            }

        }
    };

    SHA160Bit SHA_1(Bitarray bytes) {
        // (*?) I wish I could just drag the underneath comment block as a ~ canvas / textbox, somewhere to the right,
        // and that I could ~ "zoom out very much", box-select it and copy-drag it or something (it wouldn't affect the source code;
        // it could be discarded or saved "in-file")
        /*  // now, these are supposedly to be big-endian arranged; intel is little endian, which would imply that I need to
            // re-arrange them (?)
            h0 = 0x67452301
            h1 = 0xEFCDAB89
            h2 = 0x98BADCFE
            h3 = 0x10325476
            h4 = 0xC3D2E1F0
        */
//        uint32_t init_as_is[5] {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};    // LSB first
        uint32_t init_rearranged[5] {0x01234567, 0xFEDCBA98, 0xFEDCBA98, 0x76543210, 0xF0E1D2C3};   // MSB first
        // (*?) I want an alias to init_rearranged...

        bytes.Preprocess();
        Bitarray::BlockContainer blocks = bytes.BreakMessageIntoBlocks();

//        for(auto block : blocks) { }  // this doesn't work "out of the box" for raw pointers, because the type system does not know how to get its length and other type meta-data
        Bitarray::Block512& block {blocks[0]};
        for(uint64_t idx {0}; idx < blocks.count_blocks; idx++, block = blocks[idx]) {  // (*?) this "post-loop" had better execute in the order specified here (!?)
            // from now on, it is assumed that the blocks are already in an "emulated big-endian order" (they ahve been "swapped properly"; the emulation is done
                // on a little-endian machine)
            uint32_t a = init_rearranged[0];
            uint32_t b = init_rearranged[1];
            uint32_t c = init_rearranged[2];
            uint32_t d = init_rearranged[3];
            uint32_t e = init_rearranged[4];

            // temporaries
            uint32_t f {};
            uint32_t k {};
            uint32_t temp {};
            for(uint8_t i {0}; i < 80; i++) {
                if(i < 20) {
                    f = (b & c) | ((~b) & d);
                    k = /* literal 0x5A827999, assumed big-endian -> */ 0x9979825A;
                } else if (i < 40) {
                    f = b ^ c ^ d;
                    k = /* literal 0x6ED9EBA1 -> */ 0xA1EBD96E;
                } else if (i < 60) {
                    f = (b & c) | (b & d) | (c & d);
                    k = /* literal 0x8F1BBCDC -> */ 0xDCBC1B8F;
                } else {
                    f = b ^ c ^ d;
                    k = /* literal 0xCA62C1D6 -> */ 0xD6C162CA;
                }

                temp = Utilitary::leftrotate(a, 5); + f + e + k + block[i];
                e = d;
                d = c;
                c = Utilitary::leftrotate(b, 30);
                b = a;
                a = temp;
            }
            init_rearranged[0] += a;
            init_rearranged[1] += b;
            init_rearranged[2] += c;
            init_rearranged[3] += d;
            init_rearranged[4] += e;
        }

        return SHA160Bit(init_rearranged);
    }
};
#endif // HASH_HPP_INCLUDED
