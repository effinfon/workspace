#ifndef POLYNOMIAL_HPP_INCLUDED
#define POLYNOMIAL_HPP_INCLUDED

#include "FileIO.hpp"

/// TD
/*
    evaluation: naive (term by term, losing information), Horner pattern (low memory, serial),
        compute the [x^0, ... , x^n] vector and do the dot product, fork for each term (or "shard"
        depending on the number of cores available) and then join-process, etc. (?)
    addition: naive [allocate memory for max(a, b), then for each{ (+); }], could be sharded based
        on number of cores and all threads operate on the same allocated memory and independently of
        each other (not requiring mutexes), etc. (?)
    multiplication: naive (allocate a + b memory, do a for(i){ for(j){ c[i+j] += a[i]*b[j]; } } with
        the c vector being pre-allocated with 0's; note that the 0-count of i and j is very useful
        here, for the simplicity of the c[i + j] expression), FFT (*?)[complexity map for polynomials
        apparently, with cheap polynomial multiplication equivalent in the form of FFT addition (?!)],
        implement a ~ decomposition of the c[k] into required terms from a[i] and b[j] (~ to binomial
        theorem, but actually also the nice problem of writting a number in all of its possible summations
        of non-negative numbers, with the additional constraints of max(a,b) and that filter the solutions
        to only those with two terms) [this can actually be pre-computed to some degree (the pattern of
        decomposition into indices / orders) and be re-used; additional memory management: de-allocating
        pre-compute, re-computing it, predicting high-usage of it, etc.], emulate it as a sort of matrix
        (op) or vector (op) which can be parallelized [but, "if the pattern were to be embedded", it would
        still require something similar to that (pre-compute) decomposition, right (*?!)], etc.
        (!?) actually, binary multiplication on CPUs needs to do this efficienctly, what do they do ? for
            one, there would be the dot-product being added, then a shift occuring, on and on until there
            are no more shifts to do (*?, is this really correct ?), etc. (!?)
*/
/// More TD
/*
    find zeros / extract roots / decomposition into monomials (*!?): analytic closed-forms where possible,
        otherwise use numerical methods (possibly with heuristics for initial guesses), parallelized searches,
        evolutionary algorithms, maybe NN (?), etc.
    plot the (1Dim) polynomial (but yes, the graph itself is 2Dim), with zoom in and zoom out functionality,
        with panning functionality, with rotation of the graph in 3Dim, with specifiability of the interval
        of interest (and precision) for particular uses (such as generating an array of input data for another
        function, etc.)

*/
/// Applications
/*
    // operations: evaluation, addition, multiplication
    operate on polynomials of order [10^0, 10^6] [just select efficient algorithms; if this were to occur on a micro-controller though ... (*?)]
    operate on polynomials of order [10^6, 10^9] (memory usage and in-place algorithms become very important)
    operate on polynomials of order [10^9, 10^12] (GB-TB range -> stream algorithms)
    the similarity of convolution to polynomial multiplication (with some sign reversed in the iteration pattern)
*/

struct Polynomial_Homogeneous {
    uint32_t order;
    double* coefficients {};

        // convention: lower powers of x's coefficients are in the lower indices, or
            // rather, x^n's coefficient is in coefficients[n]
    Polynomial_Homogeneous(uint32_t order, double* coefficients) : order(order) {
        this->coefficients = new double[order];
        for(uint32_t idx{0}; idx < order; idx++) {
            this->coefficients[idx] = coefficients[idx];
        }
    }

    Polynomial_Homogeneous(DoubleSequence seq) : order(seq.sequence.cardinal) {
        this->coefficients = new double[order];
        for(uint32_t idx{0}; idx < order; idx++) {
            this->coefficients[idx] = seq[idx];
        }
    }
};

double evaluate_second_order_homogeneous(Polynomial_Homogeneous& polynomial, double x) {
    double x_powers[polynomial.order] {1, x};   // the first two terms
    double result {polynomial.coefficients[0] + polynomial.coefficients[1] * x};
    for(uint32_t idx {2}; idx < polynomial.order; idx++) {
        x_powers[idx] = x_powers[idx - 1] * x;
        result += x_powers[idx];
    }

    return result;

    // this should be doable efficiently by having 2 cores co-operate, one computes the
        // x's powers, while the other compures the cummulation of dot products
    // more resource consumption could produce faster results, by using fast_exp
        // and each co-routine computing its own power of x and dot product, but the
        // join procedure would be ~ "2 join together everywhere, then of those 2
        // join together again", basically a ~ log2(n) join procedure * O(c) per co-routine
    // but, this requires some sort of "thread pool" or something to easily spread tasks
        // simultaneously to all cores (*!?); what about predictability and controlling the
        // synchronicity of the cores ? would the operating system support this ? or would
        // the scheduler and other processes interfere too much ?
}
#endif // POLYNOMIAL_HPP_INCLUDED
