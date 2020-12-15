#ifndef PBINFO_HPP_INCLUDED
#define PBINFO_HPP_INCLUDED

void p401(uint32_t* array, uint32_t length) {
    // stack [n+1], [1...n] filled, [n+1] empty
    // it's a "comparison model" based problem: optimize by "minimizing the swaps"
    // objective: the input is a permutation of [1..n], use the [n+1] stack (or whatever tactic)
        // to sort things such that an element of value i is located at index i (1-count indexing is used
        // in the problem); only use the stack / array / whatever for memory [~ in-place sorting, by
        // minimizing swaps -> suggests a selection sort, and then some sort of path search ? actually,
        // I'd think the sort can be any particular one, and assuming that n is known beforehand, a
        // counting sort is obvious; all elements are distinct, so sorting is useless / unnecessary, they
        // are already "sorted" (?!); this suggest that what actually needs to be computed is the
        // "shortest permutation path" (!?)]
    // output the minimum distance / number of steps and all of the found paths of minimum length

    uint32_t n = length - 1;

} void ShortestPermutationPath(uint32_t* array, uint32_t length) { p401(array, length); }

void p2684(uint32_t* array, uint32_t length) {
    // given an array, find subsequences on it such that:
    // first, there is a constraint, that the subsequence (partition actually) be monotonic ascending;
    // the next is the problem's optimization objective: to minimize (or to maximize) the
    // number of partitions of the sequence; the elements in the subsequences need not be contiguous,
    // but either way, solve for both cases; further generalization can be made by considering both
    // ascending or descending monotonic sub-sequences

} void PartitionsWithMonotonicProperty_Optimization(uint32_t* array, uint32_t length) { p2684(uint32_t* array, uint32_t length); }

void p2141(uint32_t* array, uint32_t length, uint32_t root_order) {
    // given an array, to determine whether root(n, sum(for each(term in array))) is a "perfect root" / "natural number",
    // and if it is then compute it and (, in turn) determine its prime factor decomposition; the time constraint is
    // a maximum of 100 msec, the spatial constraint is that of 64 MB / 8 MB (I suppose it means something about program
    // size and run-time allocated memory (?)

    // primality test: quickly determine if a number can be a prime / is a prime; if it cannot be a prime,
    // then decompose it or, if it is more efficient, multiply it with another number and only decompose into
    // prime factors the result obtained right before overflowing by multiplication

    // wheh extracting factors, always take out the factors by division, and while extracting the same factor over and over,
    // avoid recomputing (i * i <= N), instead only test (N % i == 0)

} void PrimalityTest_PrimeFactorDecomposition (uint32_t* array, uint32_t length, uint32_t root_order) {
    p2141(uint32_t* array, uint32_t length, uint32_t root_order);
}
// I am thinking, how big would be a list of all prime numbers found in the uint32_t type (?)
// further, the problem constraints the root_order to {2, 3, 4}, length to [1, 5000] and the values to [1, 30'000],
    // so actually uint32_t search-space is bigger than the problem asks for

void p3398(char* string) {
    // extract all the words from the string, turn them all to lower case (case insensitivity);
    // next, compute the "k-ps" property of each word, and classify all the words in the string based
    // on this property

    // the string should be null terminated

    // for further details and ideas related to k-ps, read the problem description;
    // solution idea: "spawning points determined by the first letter", which then get filtered out by
    // checking the next letter and then the next letter, etc.

    // other suggested ideas would be: palindrome, symmetry of bounds / ends (k-ps is different
    // in the sense that it doesn't rotate the ends, but instead reads them in the same direction),
    //
} void alias /* (char* string) {
    p3398(string);
} */

void p2632(int** arrays, uint32_t length_arrays /* "num_arrays" would be more suggestive */, uint32_t* length_array) {
    // given an array of sorted arrays,

    /*
    Se dau n șiruri de numere întregi ordonate crescător, de dimensiuni d[1], d[2], …, d[n]. Dacă se interclasează șirurile
    de dimensiuni d[i] și d[j] atunci se efectuează d[i]+d[j] operații și se obține un șir de dimensiuni d[i]+d[j]. Trebuie
    interclasate toate cele n șiruri. Pentru aceasta sunt necesari exact n - 1 pași. La fiecare pas se iau două șiruri, se
    interclasează și cele două șiruri se înlocuiesc cu noul șir. Scopul este să se obțină un singur șir ordonat efectuând un
    număr minim de operații. De exemplu, dacă n=4 și șirurile au dimensiunile 1, 5, 2 și 5, atunci se poate interclasa mai
    întâi 1 și 5, se fac 6 operații și rămân 3 șiruri de lungimi 6, 2, 5. Se interclasează apoi 2 cu 5 cu un cost 7 și rămân
    două șiruri: 6 și 7. Se interclasează aceasta două cu un cost de 13 și a rămas un singur șir. În total s-au efectuat
    6 + 7 + 13 = 26 operații, dar acesta nu este numărul minim posibil.
    */
}

#endif // PBINFO_HPP_INCLUDED
