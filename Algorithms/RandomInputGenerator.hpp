#ifndef RANDOMINPUTGENERATOR_HPP_INCLUDED
#define RANDOMINPUTGENERATOR_HPP_INCLUDED

#include <random>
#include <memory>
#include <iostream>
#include <bitset>
#include <GL/glew.h>

#include "Graph.hpp"

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

AdjacencyMatrix GenerateRandomUndirectedGraphAdjacencyMatrix(uint32_t size) {

}
AdjacencyMatrix GenerateRandomDirectedGraphAdjacencyMatrix(uint32_t size) {
    std::mt19937 rand;
    AdjacencyMatrix* result = new AdjacencyMatrix(size);
}
#endif // RANDOMINPUTGENERATOR_HPP_INCLUDED
