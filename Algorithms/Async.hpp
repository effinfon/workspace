#ifndef ASYNC_HPP_INCLUDED
#define ASYNC_HPP_INCLUDED

#include <iostream>
#include <future>
/// TD
/*
    it would seem that asynchronous programming is closer to the concept of "co-routine" as
        compared to the concept of "multi-threading"

*/

// (*!?) if you think about it, operations "that do not have any `exterior side-effects`,
    // and the `internal operations` that do not have any side-effects on things that have
    // exterior side-effects", they can very well be "optimized away" (?); but, how does one
    // explicitate that, if possible, they are to be optimized away, and on the contrary, how
    // are they to be specified otherwise (!?); and, if they are used just to gain a certain
    // effect on the "state", then the optimizer could instead search for more optimal
    // operations / path of computations to reach the same state (!?)

namespace async_playground {

void foo (uint64_t bla) { ; }
void asyncFunction() {
    printf("Entered the async function.\nThe current thread's ID is %u.\n", std::this_thread::get_id());

//    for(uint64_t idx {0}; idx < 10000000; idx++) {
    for(uint64_t idx {1}; idx < 10000000; idx++) {
        try {
            uint64_t temp = (idx * idx - idx) / idx;    // a rather roundabout way to (in a sub-domain !) compute x - 1
                // (!?) damn it, C++ has run-time monitoring of arithmetic operations and, without me wanting this,
                    // will throw an exception in the case of <e.g.> x / 0 (floating operation exception); therefore,
                    // this enhances the need for using something like a lock_guard<std::mutex> instead of directly the mutex,
                    // the ensure that it gets freed; and also, a catcher for exceptions... (?!)
            foo(temp);
                // (*?) well, for some reason, the floating-point exception bypasses even this try-catch statement
                    // and crashes the whole program
        } catch(...) {
            std::cout << "An error has been encountered.\n";
        }
    }

}

int asyncFunction2(int a) {
    printf("Entered the async function.\nThe current thread's ID is %u.\n", std::this_thread::get_id());
    a = a + a;
    for(int i = 0; i < 10; i++)
        a = a + a;
    return a + 100;
}

void playground_v1() {
        // (*?) and what if there parameters to be passed to the function being called (?)
    std::future<void> fn = async(std::launch::async, asyncFunction);
    printf("The current thread's ID is %u.\n", std::this_thread::get_id());
    fn.get();

    std::future<int> fn2 = async(std::launch::async, asyncFunction2, 200);
    std::cout << "Output of async2: " << fn2.get() << "\n";
}

};
#endif // ASYNC_HPP_INCLUDED
