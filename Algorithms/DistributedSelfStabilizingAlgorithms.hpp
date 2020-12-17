#ifndef DISTRIBUTEDSELFSTABILIZINGALGORITHMS_HPP_INCLUDED
#define DISTRIBUTEDSELFSTABILIZINGALGORITHMS_HPP_INCLUDED

#include "CollectionTypes.hpp"
/// TD
/*
basically, read the wiki page and reproduce everything on the Collatz conjecture; and also bring some new ideas
    generate DAGs from the Collatz sequence; verify tyhe "proof" / analysis for it; see if it can be
        parametrized to other patterns, to produce other patterns of DAGs
    compute the histogram of the "stopping times" and render it; also render the plot (it looks interesting,
        there are ~ "wavy patterns" in it)
    there is something else that is interesting: it has a ~ "double origin" or something that creates two
        points from which each spawns a wavy pattern; also, at higher scales, the pattern seems to oscillate
        quasi-stably (or does it permanently change ?); do new such spawning points keep appearing ? what
        if one tried to adjust the distances between them (?)


*/

/// Collatz Conjecture or Syracuse Problem (yet unsolved in 2019: "why is the repeating suffix always 4 2 1, for any seed value ?")
uint64_t Collatz_v1(uint64_t seed) {
    static uint64_t count {10000};
    while(count) {
        printf("%lu ", seed);

        if(seed % 2) {
            seed *= 3;
            seed++;
        } else {
            seed /= 2;
        }

        count--;
    }
}

DynamicArray<uint64_t> IdentifyRepeatingSuffix(DynamicArray<uint64_t> sequence) {

}
#endif // DISTRIBUTEDSELFSTABILIZINGALGORITHMS_HPP_INCLUDED
