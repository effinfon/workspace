#ifndef THREADPOOL_HPP_INCLUDED
#define THREADPOOL_HPP_INCLUDED

//#include <thread>
#include <iostream>
#include <boost/thread.hpp>

bool say_yes_once() {
    static int occured = false;

    if(!occured) {occured  = true; return true;}
    return false;
}

void call_me(int n) {
    int result[] = {1, 1};
    for(int i = 2; i < n; i++) {
        int temp = result[0] + result[1];
        result[0] = result[1];
        result[1] = temp;
    }
    std::cout << result[1];
}

void example_wo() {
    if(say_yes_once()) {
        call_me(1000000);
    }
}

void example_w() {
    if(say_yes_once()) {
        boost::thread thr = boost::thread(boost::bind(&call_me, 1000000));
    }
}

#endif // THREADPOOL_HPP_INCLUDED
