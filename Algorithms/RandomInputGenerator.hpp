#ifndef RANDOMINPUTGENERATOR_HPP_INCLUDED
#define RANDOMINPUTGENERATOR_HPP_INCLUDED

#include <random>
#include <memory>
#include <iostream>
#include <bitset>
#include <GL/glew.h>

#include "Graph.hpp"

#include <random>
#include <string>

/*
    specification language for primitive types and the number of memory instances of each type
    returning a void* allocated array
    (*?) "entropy pool" and the static ctor for the RNG -> (*?) randomness can in principle only be obtained from "the outside", right ?
        or at least, "from something outside the space of what someone who has this program can measure and be certain of", the point
        being that this program alone cannot generate randomness ? but what if it could (*?), as in the uncertainty principle; maybe it
        could time itself in executing something [dependent on thread scheduling; but it wouldn't work of, say, the scheduler were to
        purposely schedule it "predictably", or if the system were "system-wide integrated and stable / predictable" (*?)]

*/
/*  SPECIFICATION (STRING) LANGUAGE

    multi-ary numeric recognition (0b, 0x, decimal by default, o for octal, etc.)

*/


struct RandomData {
    enum KnownTypes {
        byte = 0,
        integer8,
        integer16,
        integer32,
        integer64,
        unsigned8,
        unsigned16,
        unsigned32,
        unsigned64,
        float32,
        float64,
        notype
    };
    inline static int const sizeOf [notype] {1, 1, 2, 4, 8, 1, 2, 4, 8, 4, 8};

    inline static std::mt19937 RNG {}; // the entropy pool could be done throughout the running of the program, starting with the static ctor and then onwards

    std::string parserWord {};
    std::string parserCount {};
    uint64_t count [KnownTypes::notype] {};

    int IntParse(std::string string) {
        int result = 0;
        int prev_result = result;

        char const* iterator = string.c_str();
        for(int i = 0; i < string.size(); i++) {
            result *= 10;
            result += string[i] - '0';

            if(prev_result > result)
                printf("Error - IntParse: overflow\n");
        }

        return result;
    }

            // (*?) "++ forward iteration" (?!); the memory model of the iterator / dts; the memory model of
            // iteration of the machine

    void* ParseLanguageString_Language_v1(std::string string) {
init:
        for(int i = 0; i < KnownTypes::notype; i++)
            count[i] = 0;

        KnownTypes currentType {KnownTypes::notype};
        char const * iterator {string.c_str()};
        void* result {nullptr};

parser:
        parserWord.erase();
        parserCount.erase();

        // consume space, load a "word", consume '.' separator, load a "number", consume ',' separator
//        printf("Debugging: parser\n");
        while((*iterator) == ' ') { iterator++; }
        while((*iterator) >= 'a' && (*iterator) <= 'z') { parserWord += *iterator; iterator++; }
        while((*iterator) >= '0' && (*iterator) <= '9') { parserWord += *iterator; iterator++; }
        while((*iterator) == '.') { iterator++; }
        while((*iterator) >= '0' && (*iterator) <= '9') { parserCount += *iterator; iterator++; }
        while((*iterator) == ',') { iterator++; }

interpreter:
        if(parserWord == "byte") {
                currentType = KnownTypes::byte;
        } else if(parserWord == "integer8") {
                currentType = KnownTypes::integer8;
        } else if (parserWord == "integer16") {
                currentType = KnownTypes::integer16;
        } else if(parserWord == "integer32") {
                currentType = KnownTypes::integer32;
        } else if (parserWord == "integer64") {
                currentType = KnownTypes::integer64;
        } else if (parserWord == "unsigned8") {
                currentType = KnownTypes::unsigned8;
        } else if (parserWord == "unsigned16") {
                currentType = KnownTypes::unsigned16;
        } else if (parserWord == "unsigned32") {
                currentType = KnownTypes::unsigned32;
        } else if (parserWord == "unsigned64") {
                currentType = KnownTypes::unsigned64;
        } else if (parserWord == "float32") {
                currentType = KnownTypes::float32;
        } else if (parserWord == "float64") {
                currentType = KnownTypes::float64;
        } else {
                currentType = KnownTypes::notype;
        }

        if(currentType != KnownTypes::notype)
            count[currentType] += IntParse(parserCount);

        if(parserWord != "") {
//            printf("Debug: goto parser\n");
            goto parser;
        }

generator:
        uint64_t totalBytes {0};
        for(int i = 0; i < KnownTypes::notype; i++)
            totalBytes += count[i] * sizeOf[i];

        result = (void*)(new uint8_t[totalBytes]);

        uint64_t offset {0};

        for(int i = 0; i < KnownTypes::notype; i++) {
//            printf("Debugging: count[i]\n");

            while(count[i]) {
                if(i == KnownTypes::float32) {
                    *(float*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::float64) {
                    *(double*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::unsigned64) {
                    *(uint64_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::unsigned32) {
                    *(uint32_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::unsigned16) {
                    *(uint16_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::unsigned8) {
                    *(uint8_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::integer64) {
                    *(int64_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::integer32) {
                    *(int32_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::integer16) {
                    *(int16_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::integer8) {
                    *(int8_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else if(i== KnownTypes::byte) {
                    *(uint8_t*)(&((uint8_t*)result)[offset]) = RNG();
//                    offset += sizeOf[i];
                } else { ; }

                offset += sizeOf[i];
                count[i]--;
            }
        }

        return result;
    }
};


    // this template needs to generate a
        // templatized size
        // templatized type
        // use a type-specific generator
        // possibly use a particular pseudo-random generator
        // decide on a scheme for the probabilistic distribution correlation (of lack of)
            // between the elements of a tuple-type / multi-attribute type
//template<typename T
    int * generateInt(int howMany) {
        std::mt19937 rand;

        int * input = new int[howMany];
        for(int i = 0; i < howMany; i++)
            input[i] = rand();

        return input;
    }

    struct intint {
        int a;
        int b;
    };

    intint* generateIntint(int howMany) {
        std::mt19937 rand;

        intint * input = new intint[howMany];
        for(int i = 0; i < howMany; i++)
            input[i].a = rand();

            /// "decorrelation"
        rand.seed(rand());  // sadly, this does make them correlated still
        for(int i = 0; i < howMany; i++)
            input[i].b = rand();

        return input;
    }

        // after some analysis, the bit pattern swapping is incorrect; but,
            // as for the doubles, they seem reasonably good as "random input"
    double * generateDouble(int howMany) {
            /// entropic seeding (?*)
        std::mt19937 rand;

            // to me it seems that a uint64_t has little variability in the
                // leftmost bits and more in the rightmost ones, thus the bit
                // mapping from a uint64_t to a double also needs to change
        double * input = new double[howMany];
        for(int i = 0; i < howMany; i++) {
            uint64_t temp = rand(); // surprisingly, the output here was 32 bits
            temp = temp << 32;
            temp += rand();

            // 1 bit = sign, 11 bits = exp, 52 bits = mantisssa
            uint64_t sign = 0;
            uint64_t exp = 0;
            uint64_t mantissa = 0;
            std::cout << std::bitset<64>(temp).to_string() << "\n";
            sign = (temp & 0b0000000000000000000000000000000000000000000000000000000000000001) << 63;
            exp = (temp & 0b0000000000000000000000000000000000000000000000000000111111111110) << 52;
            mantissa = (temp & 0b1111111111111111111111111111111111111111111111111111000000000000);

            temp = sign + exp + mantissa;
            std::cout << std::bitset<64>(temp).to_string() << "\n";
            input[i] = *(double *)(void *) &temp;
            std::cout << input[i] << "\n\n";
        }

        return input;
    }

GLfloat** generateTriangles(int howMany, int howMuch) {
    GLfloat** result_master = new GLfloat*[howMuch];

    for(int idx_master {0}; idx_master < howMuch; idx_master++) {
        GLfloat* result = new GLfloat[howMany * 3];
        for(int idx {0}; idx < howMany; idx++) {
            result[3 * idx + 0] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            result[3 * idx + 1] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            result[3 * idx + 2] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        }
        result_master[idx_master] = result;
    }
    return result_master;
}

//AdjacencyMatrix GenerateRandomUndirectedGraphAdjacencyMatrix(uint32_t size) { }

//AdjacencyMatrix GenerateRandomDirectedGraphAdjacencyMatrix(uint32_t size) {
//    std::mt19937 rand;
//    AdjacencyMatrix* result = new AdjacencyMatrix(size);
//}

#endif // RANDOMINPUTGENERATOR_HPP_INCLUDED
