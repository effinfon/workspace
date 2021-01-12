#ifndef PRIME_HPP_INCLUDED
#define PRIME_HPP_INCLUDED

#include <pthread.h>

/// TD
/*
    default context: one that resets with each execution of the program
    loaded context (possibly from a file): stores the state of the last outputted prime,
        or even a pre-computation of the currently to be outputted, etc.
    each call to IsPrime will try to use pre-compute, if it exists, of the list of primes (albeit
        I wonder if it is performant to do so, since it might be faster to just compute things
        instead; what I'd rather have is some sort of machine that somehow learns which numbers
        are primes and which are not, but also compresses this information (?!) -> a sequence model
        for the primes found so far, a model that keeps growing dynamically whenever IsPrime() is called
        with a larger number; it would be better if IsPrime were a distributed algorithm
    (*?) can there exist multiple independent / non-intersecting / non-overlapping "prime sequences" (?) [well,
        this suggests that they ought to be infinitely long, but let's include finite ones for starters; also,
        considers cellular automata-based sequences as well (I guess this implies that the automaton has a limited
        memory, so it cannot check it's next number in the sequence for primality to an arbitrary "spatio-temporal distance / pattern distance" (!?)]
    (*?) there seem to exist "purely composite sequences" (<e.g.> 4 * k, k * 15, 9^n, etc.), but when something like
        the Mersennes primes are considered [and note (!): this all starts with (?)Euclid's(?) proof that there exist an
        infinity of primes of the kind 2^n - 1 (?)], so basically that is a proof that the sequence is infinite,
        contains an infinite number of primes, it does not prove that all the numbers in its sequence are prime (!?),
        and it seems to me to be (*!?) some sort of "check the relation betwen primality and this sequence, a sort
        of proof about the overlap of sequences" (?); (*?) if a sequence is proven to have an infinity of primes, then
        it is useful for (!?)(?!), whereas otherwise it's just a finite sequence, so (?!)(?!)
*/
/*  DISCUSSIONS

    (*?!) I think that primality can be extended to logarithms as such: primality is so far defined for multiplication, in the case of natural numbers,
        but multiplication between natural numbers is addition between logarithms; therefore, whatever multiplication means for logarithms, try to
        define a sort of primality for logarithms, then translate it back to natural numbers (*?)
*/

bool IsPrime(uint64_t tested) {
    for(uint64_t checker {2}; checker * checker <= tested; checker++) {
        if(tested % checker == 0) return false;
    }
    return true;
}
void* IsPrime_distributed_thread_v1(void* arg_void) {
    uint64_t* arg = (uint64_t*)arg_void;
    uint64_t& tested = arg[0];
    uint64_t& step = arg[1];
    uint64_t& result = arg[2];
    printf("[Debugging]\nEntered thread with step: %ul\n", step);

    for(uint64_t checker {3}; checker * checker <= tested; checker += step) {
        printf("Testing %ul against %ul\n", tested, checker);
        if(tested % checker == 0) { result = 0; printf("Found not to be prime due to %d / %d \n", tested, checker); return nullptr; }
    }

    result = 1;
    printf("This thread has not found divisors\n");
    return nullptr;
}
bool IsPrime_distributed_v1(uint64_t tested) {
    if(tested % 2 == 0) return false;

    /// TD
        // I'd like to somehow make $tested as a shared memory for the threads

    // fork -> 4 threads
    // another function that takes the step as input, and the tested number; the function will mandatorilly start on 3
    // the first thread that returns true will pre-maturely force the other threads to "return" (more like terminate)'
        // so, some sort of "forced termination / interrupt (?)" of a thread

    pthread_t thread_2;
    uint64_t arg_2[3] {tested, 2, 1};
    pthread_create(&thread_2, nullptr, IsPrime_distributed_thread_v1, (void*)arg_2);

    pthread_t thread_4;
    uint64_t arg_4[3] {tested, 4, 1};
    pthread_create(&thread_4, nullptr, IsPrime_distributed_thread_v1, (void*)arg_4);

    pthread_t thread_8;
    uint64_t arg_8[3] {tested, 8, 1};
    pthread_create(&thread_8, nullptr, IsPrime_distributed_thread_v1, (void*)arg_8);

    uint8_t active_threads[3] {1, 1, 1};
    uint64_t threads[3] {thread_2, thread_4, thread_8};

//    pthread_t thread_16;
//    uint64_t arg_16[3] {tested, 16};
//    pthread_create(&thread_16, nullptr, IsPrime_distributed_thread_v1, (void*)arg_16);
    pthread_join(thread_2, nullptr);
    pthread_join(thread_4, nullptr);
    pthread_join(thread_8, nullptr);

    // (!?) this is dangerous; if any of the threads terminates itself just after
        // any other of the threads has just returned, then there could be the case of a
        // "double cancel"; and yet, this could also be simply solved by checking if the
        // thread still exists and making some sort of "reservation for termination", something
        // like sending a signal to it and forcing it to terminate itself, as long as insurance
        // that the signal will be processed can be made (*?)
    for(uint8_t idx {0}; idx < 3; idx++) {
        if(active_threads[idx]) {
            pthread_cancel(threads[idx]);   // or std::terminate(threads[idx]); (?)
            active_threads[idx] = 0;
        }
    }

    std::cout << "thread1: " << arg_2[2] << "\nthread2: " << arg_4[2] << "\nthread3: " << arg_8[2] << "\n";
}

    // (*?) what about some branchless "arithmetic checking" of powers of 2's pre-computes (?)
    // maybe that would just take up too much memory, unperformantly
bool IsMersennePrime(uint64_t tested) {
    if(IsPrime(tested)) {
        tested++;
        while(tested != 1) {    // or "while(tested > 2) {"
            if(tested % 2 == 1) return false;
            tested /= 2;
        }
        return true;
    }
    return false;
}

    // this needs some sort of static analysis: the first time this function is called, it will
    // have logic for handling the particular case of the first prime and the increment by +1,
    // but all increments after that will be += 2 (maybe can improve on this ?); so, there is
    // need for "function morphism" (not necessarely "isomorphism), ~ to template programming;
    // I need to identify where in the program will the first call to this function occur, such
    // as to put a "mutation" in that place, but (!?) I think that this problem is possibly undecidable,
    // meaning that there are use cases that depend very much on the input at run-time
uint64_t NextPrime() {
    static uint64_t last_prime = 1;
    while(!IsPrime(++last_prime)) ;
    return last_prime;
}

    // another version would be to: "since Mersenne primes are constrained to the 2^n - 1 form,
    // then just iterate through the
uint64_t NextMersennePrime() {
    static uint64_t last_prime = 1;
    while(!IsMersennePrime(++last_prime)) ;
    return last_prime;
}

#endif // PRIME_HPP_INCLUDED
