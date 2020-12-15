#ifndef FORMATTING_HPP_INCLUDED
#define FORMATTING_HPP_INCLUDED

#include <string>

/// TD
/*
    write in normalized base 10, with exp
    write as a power of 2 times a number between [1, 2)

*/

/// Helper functions
void reverse(uint64_t& number) {
    uint64_t reverse {0};
    while(number) {
        reverse *= 10;
        reverse += number % 10;
        number /= 10;
    }
    number = reverse;
}
void reverse(uint8_t& number) {
    uint8_t reverse {0};
    while(number) {
        reverse *= 10;
        reverse += number % 10;
        number /= 10;
    }
    number = reverse;
}

std::string normalized_radix10(uint64_t number, uint64_t decimals) {
    uint8_t exp {0};
    uint64_t comparator {1}; decimals++;
    while(decimals) { comparator *= 10; decimals--; }

    while(number / comparator) { // or number / 10, which is better (*?)
        number /= 10;   // simply truncate
        exp++;
    }

    uint64_t decimal_digits {0};    // any one of these two might as well
    uint64_t decimal_cursor {1};    // reuse the memory allocated by $comparator
    while(number / 10) {
        decimal_digits += (number % 10) * decimal_cursor;
        decimal_cursor *= 10;

        number /= 10;
        exp++;
    }

    std::string result {};
    result += char(number + '0');
    result += '.';

    for(comparator = 1; comparator < decimal_cursor; comparator *= 10) {
        result += char('0' + (decimal_digits / comparator) % 10);
    }
    result += "e";

    // this would be cool actually
/*
    void reverse(uint64_t& number) {
        uint64_t reverse {0};
        while(number) {
            reverse *= 10;
            reverse += number % 10;
            number /= 10;
        }
        number = reverse;
    }
*/
    reverse(exp);

    while(exp) {
        result += char('0' + (exp % 10));
        exp /= 10;
    }

    return result;
}

//template<typename T>
std::string bitstring(uint32_t& bitstream) {
//    void bits[32] = (void*)&bitstream;    // annoying, why can't I
    void* bits = (void*)&bitstream; // the only real thing I need to know here
            // are LSB first / MSB first and the number of bits; that should
            // get templated
        // actually, I think the above $bits is not needed, since it doesn't help
            // and by using this arithmetical method, it's also independent of the
            // byte order LSB first / MSB first' but it does depend on the uint / 2
            // to behave as an "arithmetic shift" (not cyclic shift) and the bit & operation
/*
    uint32_t bitmask {0b00000000000000000000000000000001};
    while(bitmask > 0) {    // (*?) note: > 0 (one bit, "early halt") is cheaper than != 0 (all bits)

    }
*/
    uint32_t bitmask {0b10000000000000000000000000000000};
    std::string result {};
    while(bitmask > 0) {    // (*?) note: > 0 (one bit, "early halt") is cheaper than != 0 (all bits)
//        result += '0' + (bitmask & bitstream) ? 1 : 0;    // doesn't do anything, "optimized" away ?
//        result += '0' + ((bitmask & bitstream) ? 1 : 0);    // this works
        result += '0' + bool((bitmask & bitstream));  // so does this

//        std::cout << "bitmask: " << bitmask << "\n";
        // bitmask >> 1;
        bitmask /= 2;   // to avoid the risk of a cyclic shift
    }

    return result;
}
std::string bitstring(uint64_t& bitstream) {
    uint64_t bitmask {0b1000000000000000000000000000000000000000000000000000000000000000};
    std::string result {};
    while(bitmask > 0) {
        result += '0' + bool((bitmask & bitstream));
        bitmask /= 2;
    }

    return result;
}

std::string formatted_byte_size(uint64_t bytes) {
    // 1024 B - 1 KB, 1024 KB - 1 MB, 1024 MB - 1 GB, 1024 GB - 1 TB, 1024 TB - 1 PB, etc.
    // default: 2 decimals
    uint64_t order {0}; // 0 - B, 1 - KB, 2 - MB, etc.
    uint64_t comparator {1024};
    std::string result {};

    while(comparator < bytes) { comparator *= comparator; order++; }
    if(comparator == bytes) { order++; result += "1.00"; }
    else {
        comparator /= 1024;
        // 2 decimals of precision means about 6-7 "binals"
        // LAZY: for now, no decimals
        result += '0' + (bytes / comparator);
        result += ".xx";
    }

    switch(order) {
        case 0: result += "B"; break;
        case 1: result += "KB"; break;
        case 2: result += "MB"; break;
        case 3: result += "GB"; break;
        case 4: result += "TB"; break;
        case 5: result += "PB"; break;
        case 6: result += "EB"; break;
        case 7: result += "YB?"; break; // UNSURE OF SUFFIX
    }

    return result;
}
#endif // FORMATTING_HPP_INCLUDED
