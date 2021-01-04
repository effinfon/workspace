#ifndef EXTENDEDUINT_HPP_INCLUDED
#define EXTENDEDUINT_HPP_INCLUDED

#include <algorithm>

struct Uint {
    uint32_t* value {nullptr};    // [0] is lsb
    uint64_t count {0};

    Uint() {}
/*td; test*/    Uint(uint32_t value) : count(1) {
        this->value = new uint32_t[1] {value};  // (*?) do check that does gets interpreted as intended
    }
/* td; */    Uint(std::string value) {
        // a study of the mapping of the decimal base onto the binary base,
        // in regards to the maximum number of decimal digits that can fit
        // in a 32 binary digit number space, indifferently of the decimal
        // digits used (*?)[~ the "maximal closed mapping" based on digit length]
        static const uint8_t maximumDecimalDigits {9};  // this is currently a naive guess
            // I also want to mention that such value systems should use the type system differently,
            // the type system will automatically attribute types such as uin8_t or uint16_t or int32_t
            // or float or double or etc. based on the set of possible values the variable can take on,
            // because me, as a programmer, writting uint8_t, do not express any "abstract and clear and pure intent",
            // but insteda I explicitate the result of already an optimization problem [basically, a sort of
            // "(counter-)translation" already (!?)]
        uint8_t counter {0};    // (*?) in language design, the notion of defining everything from very few axioms
            // is comendable; but, (!?) it seems to also be, without the further use of complexity, a cause of
            // complication for efficientizing computation to practical levels... (*!?)

        // (!?) "pre-counting" and "post-counting", coupled with "pre-comparison" and "post-comparison"
        // "while(counter < maximumDecimalDigits) { process_a_digit(); counter++; }" is a "post-counting",
        // meaning that each increment signifies an act that has already confirmedly occured, with pre-checking (*?);
        // the result is that there is an offset of 1, just so that the comparator can be "idx < maximum" instead of "idx <= (maximum - 1)"

        uint64_t idx {0};
        uint64_t accumulator {0};
        uint32_t word {0};  // I wanted to call this "register"
        uint64_t decimalPosition {1};
        // the $value string should be reversed; it is more "dangerous" / "unsafe" to decrement in size than to increment (unless
            // the "idx != 0" condition is used, but then there would be an ugly repeat of code for that particular case
        std::reverse(value.begin(), value.end()); // (!?)

        while(idx < value.size()) {
            // accumulate into a (?"super-word"?)
            while(counter < maximumDecimalDigits && accumulator <= 0xFFFFFFFF) { // (*?) any loop has "pre-" and "post-" operations, apparently, which is an
                                                    // useful classification; then there's the "(loop) body"
                                                // (!?) I need a better system for generating "limits"
                // accumulator *= 10;   // (*?) using this method gives rise to the same pattern as with little endianness, those "blocks" with "normal order (msb left, lsb right)", but only the
                                        // blocks themselves are in "reversed order (lsb left, msb right)"
                accumulator += decimalPosition * (value[idx++] - '0');
                counter++;
                decimalPosition *= 10;  // placing such an operation "post-loop" will always produce a "useless operation" when the loop has to end,
                        // but placing it at the beginning is also... "unfeasible" ? (*?); it would require a Uint which multiplied by 10 to result
                        // in 1, but the only such number is 0.1 which does not belong to Uint; using float or double could work except for gaps with some digits (?)

                        // (!?) does float or double have perfect precision for all cases of "0.x * 10 = x", for x a decimal (!?)
            }
            // "transfer the accumulation into a word"
            // use an startian / endian -independent mechanism, by "type casting, down-sizing / down-sampling"
            word = accumulator;
            accumulator -= word;    // "truncate" in the decimal base; it doesn't (generally) map to a nice binary-base, shift operation (*?)

            counter = 0;
            decimalPosition = 1;
        }
        // (!?) now, how am I to visualize how this program actually works ? testing and debugging are awfully painful; the linear execution of the
            // program is a painful, slow, inefficient interface
    }
    Uint(Uint const & copy) : count(copy.count) {
        this->value = new uint32_t[this->count];
        for(uint64_t idx {0}; idx < this->count; idx++) {
            this->value[idx] = copy.value[idx];
        }
    }

    uint32_t& operator [] (uint64_t index) {
        if(index < count)
            return value[index];
        else {
            uint32_t dummy {0};
            return dummy;   // (*?) actually, this should cause a memory access error
                // when the caller tries to access it, right (*?)
                // (*?) so then, either return a default reference, or a "dummy reference",
                // but how to implement this "dummy reference" (?)
        }
    }
};

// "definition wise it is static" because this way I do not have to deal with that "*this" pointer syntax, but (!?)
// this is somewhat rubbish; the standard forces me to define the operation outside the dts's definition
    // (*?) I wonder what "unflexibility" does their compilation process have that forces them to force me
    // to do this (?)
/* to be tested */ static Uint operator + (Uint a, Uint b) {
    Uint result {};
    result.count = ((a.count > b.count) ? a.count : b.count) + 1;
    result.value = new uint32_t[result.count]; // a "grow by one / shrink by one" mechanism
            // for the heap memory management would be very useful
    std::cout << "[Debugging]\ncount: " << result.count << "\n";
    uint64_t accumulator {0};
    uint64_t min_count = (a.count < b.count) ? a.count : b.count;

        // if either of them is on 0-length, then simply return the other operand, but this is just a ~ "computation culling",
            // it is irrelevant if the other operand is also of 0-length (*?)
    if(a.count == 0) return Uint(b);
    else if (b.count == 0) return Uint(a);

    uint64_t idx {0};
    for(; idx < min_count; idx++) {
        uint32_t temp_a = a.value[idx]; // even with these, I still hope that it's not interpreting the uint32_t pointer itself as an in-place uint64_t (*?)
        uint32_t temp_b = b.value[idx];
        accumulator += (uint64_t)temp_a + (uint64_t)temp_b;
        result.value[idx] = (uint32_t)accumulator;

        std::cout << "[Loop step debugging]\ntemp_a: " << temp_a << "\ntemp_b: " << temp_b << "\naccumulator: " << accumulator;

        accumulator -= result.value[idx];
        std::cout << "\naccumulator-= : " << accumulator;
//        accumulator >> 32;    // interesting, the shift doesn't work properly, but the arithmetic shift sure does
        accumulator /= 65536;
        accumulator /= 65536;
        std::cout << "\naccumulator>>32 : " << accumulator << "\n";
    }

    uint64_t& max_count = min_count;    // I hope what this does is to re-alias the variable; it is annoying, but basically
        // I have to manually explicitate that memory that apparently isn't used anymore, I intend to re-purpose it; and to
        // keep things "clear" as a programmer, I also use a different identifier, to suggest the new purpose of the variable
    max_count = a.count + b.count - min_count;  // avoiding another if, given as known that min_count = min(a.count, b.count)
    Uint& max = (a.count > b.count) ? a : b;    // so I still couldn't avoid this
    for(; idx < max_count; idx++) {
//        accumulator += (uint64_t)a.value[idx] + (uint64_t)b.value[idx];   // although min_count -> max_count worked, but now I still need
                    // to know which of the two arrays is longer
        accumulator += (uint64_t)max.value[idx];
        result.value[idx] = (uint32_t)accumulator;

        std::cout << "[Loop step debugging]\ntemp: " << ((uint64_t)max.value[idx]) << "\naccumulator: " << accumulator;

        accumulator -= result.value[idx];
        std::cout << "\naccumulator-= : " << accumulator;
//        accumulator >> 32;    // let's try replacing this with a double division with 2^16
        accumulator /= 65536;
        accumulator /= 65536;
        std::cout << "\naccumulator>>32 : " << accumulator << "\n";
    }

    if(accumulator != 0) {  // so the allocated +1 is being used
        result.value[idx] = accumulator;
        std::cout << "[Debugging last index]\naccumulator: " << accumulator;
        accumulator -= result.value[idx];
        std::cout << "\naccumulator-= : " << accumulator << "\n";
    } else {    // it is not being used; I should deallocate it, but since that's a pain, I will just substract the count
        result.count--;
    }

    return result;  // (*?) now, will it be uselessly copied on return, or moved (?)
}

static Uint operator * (Uint a, Uint b) {
    Uint result {};
    result.count = a.count + b.count;   // (*?) this needs to be better understood; one way to look at these is as the "number system's
            // floor exponent" [which is basically the number of digits to the left, with a very important +1 which is actually not required
            // in this case, because that never reached; it's about the 10 as compared to the 9, and 100 * 1000 = 100000 does require 6 digits,
            // basically (2 + 3) + 1, but that's the first occurence for the +1 to be needed, and in multiplication one deals with exactly the
            // last arithmetic / decimal configuration beneath this (!?)]
    result.value = new uint32_t[result.count];

    std::cout << "[Debugging]\ncount_a: " << a.count << "\ncount_b: " << b.count << "\nresult count: " << result.count <<"\n";

    Uint& min = (a.count < b.count) ? a : b;
    Uint& max = (a.count > b.count) ? a : b;

    uint64_t idx {0};
    uint64_t accumulator {1};

    // on the other hand, there is a slight problem here; all blocks need to be paired and multiplied with all blocks;
    // for "simplicity", one could use the addition operation already defined, and only define here the part where a single
    // block gets multiplied with all the blocks of the other Uint, and an addition accumulation on top of all those sub-tasks;
    // (!?) but isn't there a better way to integrate this ~ "distributivity" (?)
    for(; idx < min.count; idx++) {
        //accumulator
    }
}

#endif // EXTENDEDUINT_HPP_INCLUDED
