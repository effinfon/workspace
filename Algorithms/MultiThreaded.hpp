#ifndef MULTITHREADED_HPP_INCLUDED
#define MULTITHREADED_HPP_INCLUDED

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
//#include <algorithm>

//#include <cstdlib>
//#include <string>
#include <vector>
#include <ctime>
//#include <numeric>
//#include <cmath>
//#include <sstream>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "Prime.hpp"

/// TD
/*
    a waiting loop with a "reasonable" timeout (*?)
    a "thread pool" (*?)
    shared memory between multiple threads and inter-thread communication (so far I am limited to
        // atomic and mutex, with the addition of lock_guard); but the case remains that there is
        // no nice syntax for explicitating "thread, shared memory" (*?); there are ways by simply
        // making the variables "global" to the functions the threads execute and/or the main thread,
        // but actually this mechanism too has interesting merits that need more studying (*!?); the
        // only place to speciffy "thread, private memory" seems to be at the entrance point's interface,
        // and (eventually) all along the scopes of the deriving logic structure from those entry points (so,
        // this includes static variables as yet another mechanism for shared memory, but all of the local variables
        // are (probably ?) the thread's private memory, and depending on the execution's logic / logic flow at run-time
        // it might also grow / shrink ~ arbitrarily
    (?) are there mechanisms to timeout a thread ? the more "sophisticated" requirement was to detect whether a thread
        // has become "stuck" / entered an infinite loop, or whether it can decidably be proven that a thread will never halt (*!?),
        // in order to terminate it (?)
*/
/*
    how to get the right time in the system, because as it is it says it's in year 120
        and the "year day" / ~ "date" is november 25 (11 25) instead of december 25
    after that is fixed, what about creating a background process that sleeps up to some
        timedate, then "awakens" / resumes, does a system call with some script, saves some
        text into a file and then sleeps again until the next day (or minute, in which case
        it could also be a ~ "logger", such as "top >> log", but with append instead of overwrite)

*/

void findOdd(std::promise<uint64_t>&& OddSumPromise, uint64_t start, uint64_t end) {
    uint64_t OddSum = 0;
    for(uint64_t idx {0}; idx <= end; idx++) {
        if(idx & 1) {   // vs "idx % 2 == 1"
            OddSum += idx;
        }
    }
    OddSumPromise.set_value(OddSum);
}

void test1(uint64_t end) {
    uint64_t start = 0;

    std::promise<uint64_t> OddSum;
    std::future<uint64_t> OddFuture = OddSum.get_future();

    std::thread t1(findOdd, std::move(OddSum), start, end);

    OddFuture.get();
    t1.join();
//    std::cout << "Result: " << OddFuture.get() << "\n";
}

namespace playground {

    // (*?) what exactly happens when a "multi-thread unaware function, with internal
    // state" gets to be called (almost) simultaneously by multiple threads (?)
int GetRandom(int max) {
    srand(time(NULL));
    return rand() % max;
}

char* GetTime() {
    time_t timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    return ctime(&timenow);
}

void ExecuteThread (int id) {
    auto nowTime = std::chrono::system_clock::now();    // supposedly this is in milliseconds by default
    std::time_t sleepTime = std::chrono::system_clock::to_time_t(nowTime);
    tm myLocalTime = *localtime(&sleepTime);    // (*?) time or timezone; and why is this needed, is the time encoded (?)

    std::cout << "[Debugging]\nid: " << id << "\ntime at sleep: " << std::ctime(&sleepTime) << "\n";
        // so ctime(time_t*) produces what ? a string of the hour analogous to $tm or what (?)
    std::cout << "month " << myLocalTime.tm_mon << "\nday " << myLocalTime.tm_mday
        << "\nyear " << myLocalTime.tm_year << "\n" << myLocalTime.tm_hour << ":"
        << myLocalTime.tm_min << "::" << myLocalTime.tm_sec << "("
        << myLocalTime.tm_zone << ")\n";
    std::thread::id threadID = std::this_thread::get_id();

    std::cout << "Actual id is (warning: native_handler_type) " << threadID << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    nowTime = std::chrono::system_clock::now();
    time_t awakeTime = std::chrono::system_clock::to_time_t(nowTime);
    std::cout << ctime(&awakeTime) << "\n";
}

double accountBalanceLow_v1 = 100;
double accountBalanceLow_v2 = 100;
std::mutex acctLockLow; // (*?) this doesn't seem to be "integrated into the type system",
    // and by that I mean that the acctLocklow doesn't seem to be attributed / linked with
    // the variable "it protects", so the mutex is instead used "logically" as a ~ "thread block",
    // but the result of this is that a single mutex can "protect multiple things"

void Indirection(int id, double withdrawal) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << id << " tries to withdraw " << withdrawal
        << " at time " << GetTime() << "\n";
    if((accountBalanceLow_v1 - withdrawal) >= 0) {
        accountBalanceLow_v1 -= withdrawal;
        std::cout << "New balance is " << accountBalanceLow_v1 << "\n";
    } else {
        std::cout << "Not enough money for withdrawal. Remainig: " << accountBalanceLow_v1 << "\n";
    }
}

void GetMoney_v1(int id, double withdrawal) {   // exception safe
    std::lock_guard<std::mutex> lock(acctLockLow);
    Indirection(id, withdrawal);
}

void GetMoney_v2(int id, double withdrawal) {   // withdrawal unsafe
    acctLockLow.lock();
    Indirection(id, withdrawal);
    acctLockLow.unlock();
}

//void FindPrimes(uint64_t id, uint64_t start, uint64_t end, std::vector<uint64_t>& vector, clock_t& clock_end) {
void FindPrimes_v1(uint64_t id, uint64_t start, uint64_t end, std::vector<uint64_t>* vector, clock_t* clock_end) {
    for(uint64_t tested {start}; tested <= end; tested++) {    // when would it be more performant,
            // if ever, to write "indexed < end + 1" (?); well, then there's the need for end to be forced
            // to have a reserved state at uint64_t.max_value though (*?)
        if(IsPrime(tested)) {
            vector->push_back(tested);
//            printf("Adding prime %u\n", tested);
        }
    }

    std::cout << "Thread id " << id << " is returning.\n";
    *clock_end = clock();
    return;
}

std::mutex vectLock;
std::vector<uint64_t> primeVect;

void FindPrimes_v2(uint64_t start, uint64_t end) {
    for(; start <= end; start++) {
        if(IsPrime(start)) {
            vectLock.lock();
            primeVect.push_back(start);
            vectLock.unlock();
        }
    }
}

void ThreadMaster_FindPrimes_v2(uint64_t start, uint64_t end, uint64_t numThreads) {
    std::vector<std::thread> threads;
    uint64_t step = (end - 1 + numThreads) / numThreads;    // ~ floor of the division
    uint64_t end_step = start + step;
    for(uint64_t idx {0}; idx < numThreads; idx++) {
        threads.push_back(std::thread(FindPrimes_v2, start, ((end_step < end) ? end_step : end)));
        start += step;
        end_step += step;
    }
    for(auto& thread : threads) {
        thread.join();
    }
}

void testPlayground1() {
    std::cout << "Phase 1: \n\n";
    std::thread th1 (ExecuteThread, 1);
    std::thread th2 (ExecuteThread, 2);
    th1.join();
    th2.join();

    std::cout << "\nPhase 2: \n\n";
    std::thread threads[10];    // (*?) I wonder if this calls any default constructors (?)
            // and what is put into those memory blocks / structs
    for(uint64_t idx {0}; idx < sizeof(threads) / sizeof(std::thread); idx++) {
        threads[idx] = std::thread(GetMoney_v1, idx, GetRandom(100));
//        threads[idx] = std::thread(GetMoney_v2, idx, GetRandom(100)); // well, this causes a crash
    }
    for(uint64_t idx {0}; idx < sizeof(threads) / sizeof(std::thread); idx++) {
        threads[idx].join();
    }
}

    // (!?) so, multi-threading the search-space itself is all nice and dandy, but distributed algorithms
        // need to go all the way; what do I mean by that ? not only is it required that the problem space be
        // partitioned like this, but also the algorithm used to test if a number is prime should itself be
        // made distributed; and there the discussion begins: if it can be made into a "memory / learning model",
        // then the ideal would be for that model to be parallelizable, otherwise for there to be a set of models
        // which, again, independently cover the algorithm's space of cases (all of them -> coverage analysis);
        // there are other possibilities such as probabilistic computing, but when the answer is "qualitative"
        // instead of "quantitative", then an "approximate answer" does not have the same meaning (?!)
    // (!?) there is also the aspect that threads are really useful as long as they are covered by a corresponding
        // number of cores to execute them, so the choice of number of threads is really an attempt to maximize
        // the utilization of the hardware; now, in concurrence with maximizing number of cores used, there's also
        // consideration of maximizing things such as "arithmetic parallelization", "vector processors", "pre-fetching
        // and locality", minimizing ~ "cache distance" and "cache misses", etc.; the main point here is to discuss about
        // GPGPU parallelization / implementation of these algorithms (!?)
void testPlayground2() {
    std::cout << "Phase 1: \n\n";

    const uint64_t step = 1000000;
    std::thread threads[10];
    std::vector<uint64_t> vectors[10];
    clock_t clocks_start[10];
    clock_t clocks_end[10];

    for(uint64_t idx {0}; idx < sizeof(threads) / sizeof(std::thread); idx++) {
        clocks_start[idx] = clock();
        printf("Starting thread %u at time %f.\n", idx, ((double)clocks_start[idx] / (double)CLOCKS_PER_SEC));
        threads[idx] = std::thread(FindPrimes_v1, idx, (idx * step), ((idx + 1) * step - 1), &(vectors[idx]), &(clocks_end[idx]));
    }
    for(uint64_t idx {0}; idx < sizeof(threads) / sizeof(std::thread); idx++) {
        threads[idx].join();
        printf("Execution time for thread %u: %f\n", idx, ((double)(clocks_end[idx] - clocks_start[idx]) / double(CLOCKS_PER_SEC)));
    }
}

void testPlayground3(uint64_t start, uint64_t end, uint64_t numThreads) {
    time_t timeBegin = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    ThreadMaster_FindPrimes_v2(start, end, numThreads);
    time_t timeEnd = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "Time elapsed: " << (timeEnd - timeEnd) << "\n";
    std::cout << "Primes found: " << primeVect.size() << "\n";
}
};

namespace SFMLMultiThreading {
    // (*?) the baseline seems to be that before burrowing, one needs to "deactivate the context" of a thread (apparently each thread has its own OpenGL context ?)
    // (*?) also, it seems that whenever something is done to sf::RenderWindow on a (different) thread, it implicitly activates the OpenGL context for that thread

    void CloseWindow(sf::RenderWindow* window) {
        window->close();
        window->setActive(false);
    }

    void test1() {
        sf::RenderWindow window;
        window.create(sf::VideoMode(120, 120), "Title");
        window.setActive(false);
        sf::Thread thread = sf::Thread(CloseWindow, &window);
        thread.launch();    // (*?) I would bet that this is somehow just a wrapper of sorts for std::Thread (?)
    }

};
#endif // MULTITHREADED_HPP_INCLUDED
