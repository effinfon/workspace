#ifndef SEARCH_HPP_INCLUDED
#define SEARCH_HPP_INCLUDED

#define index_type uint64_t
#define count_type uint64_t

/// Discussions
/*
    I think that the sorting algorithms should offer mechanisms that improve the
        selection of the searching algorithm; the other option is for there to be
        a separate module that selects the search algorithm and sets it / attaches
        it to the data in a struct (?); or there is some background process / co-routine
        that monitors the data being searched repeatedly and adapts which algorithm
        is selected for it
    what is the smallest possible average path length for a search based on comparisons (!?);
        I suppose it is log2(n) exactly, but how is the average affected by having non-uniform paths ?
*/

    // global definition(s) and local definition(s); something inbetween (*?)
#define NO_MATCH -1
#define GOTO_MODE
#define FIRST_OCCURENCE
//#define LAST_OCCURENCE    // the #elifdef doesn't seem to work...

#define MIDDLE_FLOOR
//#define MIDDLE_CEILING    // not tested, nor verified; just intuitionistic


#endif // SEARCH_HPP_INCLUDED
