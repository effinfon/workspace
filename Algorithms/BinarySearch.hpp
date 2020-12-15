#ifndef BINARYSEARCH_HPP_INCLUDED
#define BINARYSEARCH_HPP_INCLUDED

#include "Search.hpp"

/// Observations
/*
    it would seem that the structured programming paradigm is about
        having attributed a single property to every goto label (*?),
        and also, that property is locally expressed with the label (or
        rather, the explicitation of the condition itself, plus some syntax,
        form up the label itself)
    (L + R) / 2 involves the definition of the concepts "floor" and "ceiling"
    ...
*/

/// TD
/*
    properly handle the implementation of the "no match" reserved
        state of the function's return (any calling function needs
        to be able to locally become aware {or the programmer rather,
        but there is some nuance here} of the "convention"
*/

/*
    given an array A of n elements,
    with property A[i] <= A[i+1] for i[0, n-2] (*?),
    and a target T

    (1) L := 0, R := n - 1, exists / allocate m
    (2) if(L > R) { "no match", halt, return reserved_state; }
    (3) m = L/2 + R/2 + (L%2 && R%2);   // avoid overflow
    (4) if(A[m] < T) { L = m + 1; goto (2); }
    (5) else if(A[m] > T) { R = m - 1; goto (2); }
    (6) else { halt, return m; }
*/

/// considerations
/*
    it doesn't guarantee that the first appearance of the target is being returned,
        in arrays with duplicates

*/


index_type binary_search_v1(int* array, count_type cardinal, int target) {
    index_type Left {0}, Right {cardinal - 1}, middle {};   // middle: just allocate
#ifdef GOTO_MODE
repeat:
    #ifdef FIRST_OCCURENCE
        if(Left > Right) { while(array[middle - 1] == target) middle--; return NO_MATCH; }
    #endif // FIRST_OCCURENCE
    #ifdef LAST_OCCURENCE
        if(Left > Right) { while(array[middle + 1] == target && middle + 1 < target) middle++; return NO_MATCH; }
    #else
//        if(Left > Right) { return NO_MATCH; }
    #endif // LAST_OCCURENCE
#ifdef MIDDLE_FLOOR
    middle = Left / 2 + Right / 2 + (Left % 2 && Right % 2);
#endif
#ifdef MIDDLE_CEILING
    middle = Left / 2 + Right / 2 + (Left % 2) + (Right % 2);
#endif
    if(array[middle] < target) { Left = middle + 1; goto repeat; }
    else if(array[middle] > target) { Right = middle - 1; goto repeat; }
    else // -> would it add any goto's to the program or not ? I'd think not...
        return middle;
#else
    while(Left <= Right) {  // notice the "conditional expression's inversion"
        middle = Left / 2 + Right / 2 + (Left % 2 && Right % 2);    // FLOOR vs CEILING, again
        if(array[middle] < target) { Left = middle + 1; }
        else if(array[middle] > target) { Right = middle - 1; }
    }
    return NO_MATCH;
#endif // GOTO_MODE
}


index_type binary_search_v2(int* array, count_type cardinal, int target) {
    index_type Left {0}, Right {cardinal - 1}, middle {};   // middle: just allocate

    while(Left != Right) {
        middle = Left / 2 + Right / 2 + (Left % 2 && Right % 2);

        if(array[middle] < target) { Left = middle + 1; }
        else { Right = middle; }
    }
    if(array[middle] == target) return middle;
    else { return NO_MATCH; }
}
#endif // BINARYSEARCH_HPP_INCLUDED
