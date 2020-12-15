#ifndef PRIMALITYTEST_HPP_INCLUDED
#define PRIMALITYTEST_HPP_INCLUDED

/// TD
/* (*) interesting derived problems (?)
    prove whether any sum sequence of primes is a unique number or not (if yes, then in the sieve_Eratosthenes_v1, each resultant number can be uniquely decomposed (or even memorized) to a unique sequence of primes
    produce a visualization / dts from the repeat patterns of patterns of the kind "product(pattern^k)" <e.g.> (2 * 5) ^ k, or (2^3 * 5^2 * 7^1 * 11^34 * 103^789) ^ k, etc.

*/


#define count_type uint32_t

// (!?) it is very interesting to note how using a particular memory / spatial pattern
    // can actually result in less time complexity, from the POV of small rearrangements
    // of the iteration pattern (?!)
int* sieve_Eratosthenes_v1(count_type size) {
    int* array = new int[size + 1] {};

    for(count_type prime = 2; prime <= size; prime++) {
        if(array[prime] == 0) {
            array[0] += prime;  // optional: cummulate the sum of all prime numbers here
            for(count_type idx = 2 * prime; idx <= size; idx += prime)
                array[idx] += prime;
        }
    }

    return array;
}

int* sieve_Eratosthenes_v0(count_type size) {
    int* array = new int[size + 1];
    count_type i {2};
    count_type j {2};

    for(array[1] = 0, i = 2; i <= size; i++) array[i] = 1;

    for(i = 2; i <= size / 2; i++) {
        for(j = 2; j <= size / i; j++) array[i * j] = 0;
    }

    return array;
}
///  Considerents for the sieve:
    // adapt the algorithm for cacheline and maximizing the compute time in ratio / report to the cacheline I/O,
        // thus whether it is required to keep a cache of the identified primes (or to recheck the array block as needed, or
        // to propagate them in some cases, etc.) and to break the array into blocks; as it is, this is a ~ "line restarting,
        // n^2 or (n-1)n/2 complexity algorithm", so it does create cache misses for long arrays because it keeps being moved
        // in and out of the cache; so, instead, keep a growing list of primes which constantly get checked, and also break
        // the array into blocks, turning the algorithm sort of into a "stream algorithm (with a growing track list)"
    //

#endif // PRIMALITYTEST_HPP_INCLUDED
