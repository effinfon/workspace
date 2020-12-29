#ifndef ASYNC_HPP_INCLUDED
#define ASYNC_HPP_INCLUDED

#include <iostream>
#include <thread>
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

    // (!?) warning: this function is dangerous; the compiled program behaved unexpectedly,
        // always computing that the argument int a := 0, when instead it aws 123 or 200
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

    int input2 = 200;
    std::future<int> fn2 = async(std::launch::async, asyncFunction2, input2);
    std::cout << "Output of async2: " << fn2.get() << "\n";
    if(fn2.valid())
        fn2.get();
    else
        printf("Invalid; it has already been get().\n");
}

// (*?) to me it seems like promises are "the same" as thread.join(), except
    // any thread that's responsible for setting a promise does not necessarely
    // have to close after setting the promise; on the other hand, if a promise is
    // shared between multiple threads, does future.get() still block ? I mean that
    // there could very well be multiple points where the promise is promise.set() (*?)
int asyncFunction3(uint64_t value, std::promise<int>& prom) {
    std::this_thread::sleep_for(std::chrono::seconds(2));

//    std::future<int> fut = prom.get_future(); // (*?) futures cannot be "extracted" multiple times
        // due to that, even this function (which will be executed by two threads or some other number of threads)
        // will throw a future_error when one tries to get_future() and check if it's still valid;
    // (*?) thus, a promise should only be passed by reference to those threads which are meant to return a future,
    // the "promise" is a sort of "reference ownership" mechanism, not type-integrated but at least which throws exceptions,
    // but then crashes the program (?); better integration with the type system could

//    if(fut.valid())
        prom.set_value(200 + value);
//    else
//        printf("A thread tried to write to an already fulfilled promise.\n");
}

void playground_v2() {
    {
    std::promise<int> prom;
        // (*?) but, what is the purpose of getting the future of a promise from here ? can this be done twice or what ?
            // is it done between the ~ "receiver thread" and the "setter thread" (?)
        // (*?) it has now been noticed that the "setter thread" does at no point "get the future of the promise", but
            // instead directly set a value onto the promise; the future remains internal to the promise
    std::future<int> fut = prom.get_future();   // (*?) this really makes it seem like std::future<> is a ~ "reference type"

    std::thread t1 {asyncFunction3, 123, ref(prom)};
    //std::thread t2 {asyncFunction3, 456, ref(prom)};

    std::cout << "Get promise: " << fut.get() << "\n";
    t1.join();  // as can be seen here, the promise has already been set, but the thread
                // does not have to stop at that point; so far, a promise seems to be a sort
                // of "an asynch composed with a mutex" (*?) [but even so, it blocks only until
                // the first write to the mutex / promise; another variation would be one that
                // "un-blocks" / "de-blocks" upon different conditions, such as a counting of
                // writes to the mutex, or some other mutex being written to, etc. (*?)
    //t2.join();
    if(fut.valid()) // (*?) but, "retrieval" from a future can be done in multiple places, and there is
                    // a ~ "safety check" for this with future.valid()
        std::cout << "Get promise: " << fut.get() << "\n";
    else
        printf("This future has already been retrieved.\n");
    }
    // (*?( deallocate the promise, allocate it again, send it to another thread, and this
        // time thread.join() and only afterwards future.get()
    {
    std::promise<int> prom;
    // this time skip the get future step

    std::thread t1 {asyncFunction3, 321, ref(prom)};
    t1.join();
        // (*?) so one unavoidably has to get the future of a promise, to "get the value out"
    std::cout << "Promise result: " << prom.get_future().get() << "\n";
    }
}

};
#endif // ASYNC_HPP_INCLUDED
