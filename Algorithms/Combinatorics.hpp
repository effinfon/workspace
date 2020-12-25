#ifndef COMBINATORICS_HPP_INCLUDED
#define COMBINATORICS_HPP_INCLUDED

// (!?) how can such "bad" / "unperformant" definitions be automatically
    // translated to more performant algorithms (?); then again, the performance
    // of such algorithms needs to be disputed in terms of the machine that computes
    // the algorithm (?!); but even so, there keeps emerging this nagging idea that
    // there is "obvious (abstract) redundancy" in the algorithm, but I start to wonder
    // about that now (*?)
uint64_t Factorial(uint64_t n) {
    if(n == 0) return 1;
    return n * Factorial(n - 1);
}

#endif // COMBINATORICS_HPP_INCLUDED
