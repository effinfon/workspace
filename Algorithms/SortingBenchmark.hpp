#ifndef SORTINGBENCHMARK_HPP_INCLUDED
#define SORTINGBENCHMARK_HPP_INCLUDED

#include <pthread.h>
#include <benchmark/benchmark.h>
using namespace benchmark;

// CPU time, system time, user time, total time
// # of comparisons, # of swaps
// algorithm name
// histogram of the swaps, encoded lossy, for each algorithm for each input case (?)
// list of "sorting properties" for each algorithm
// (*?) a way of finding the "segments" where a particular algorithm seems to
    // be most efficient; (maybe measure the number and time of occurence for when
    // a "final swap" is done (need to have the dts pre-sorted so that this can be compared
    // and need a way to ensure that from the algorithm's POV that is also a "final swap" and
    // not just transitory

    //BenchmarkName name;
    //BenchmarkReporter reporter;
    //double BigOFunc(iteration_count);
    //benchmark::


#endif // SORTINGBENCHMARK_HPP_INCLUDED
