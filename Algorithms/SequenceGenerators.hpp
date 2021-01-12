#ifndef SEQUENCEGENERATORS_HPP_INCLUDED
#define SEQUENCEGENERATORS_HPP_INCLUDED

/**
    the pattern is what defines the sequence; it needs to be "generic", reusable with any other kinds of data (well, at least it needs
        to be reusable with any kind of integer numeric; they need to be mappable in arbitrary ways, the "scope" needs to be able to be changed
        arbitrarily, etc.)
    a visualization mechanism is needed for all the "learned" sequences / patterns (~ a "space", or maybe a graph)
    (*?) for a given length of a string and a finite set of states, there is a finite state-space and thus a finite number of possible "permutations"
        which could take a sequence into an ordering of the same sequence (this basically states that unordered compression can be done first and afterwards
        the search for a permutation would turn it into an ordered compression)
    (*?) the generators are actually sort of similar to the objective functions actually; a generator would cover a set of patterns,
         and when compressing, one would search which generator with which seed and up to what length will generate the sequence; there
         could be "search optimizations" such that the program can ~ "search by constraint" which generator should have an instantiation
         that fits the sequence, or maybe that there even isn't a know one yet (?!) [this property would be seen as a sort of sorting property
         over the abstract search-space of the generators; it would probably itself impose conditions on the solution generators (*?!)]
    (*!?) could "div, mod, offset, shift, ?? etc." functions be turing complete (?!); they would constitute a search-space for functions if they were;
        but actually, any turing complete machine is a feasible search-space for the abstraction that is function space(s) (?!); it seems more to be a
        question of each having a particular complexity map, thus different "computational distances" until they reach specific sequences / functions;
        there are also considerents of the performance of the function from the perspective of the "abstract machine", because said function might have
        better performance on a different abstract machine
        (?!) but how does that get to be found out ? and besides, what would be the general search-space that goes beyond choosing specific Turing complete
            abstract machines in which's language space to search (?!!); well, one naive way is to somehow define the space of all abstract machines, but ... (?!)
    (*?) I end up thinking that essentially I cannot get away from having a ~ "try all possible combinations of instructions that the machine supports, find the
        specification(s) to which each sequence of instructions validates, and gather a knowledge base" (?!)
    (*!?) how to visualize a generator that is "instantiatable" as a ~ "single mapping space" (?!); it would allow better seeing pseudo-generators, and what makes them
        instantiatable, what does the seed essentially do, how it acts as a ~ "switch" between different paths and what determines what those paths are, eventually how
        to adjust the paths and what kind of effects does a change in the function have on all the paths across all seeds (~ abstract algebra sort of analysis)
    ...
*/

/// initially, ~ "unordered compression"; a permutation function can turn it into an ordered sequence (which is another search-space)
// catalan numbers
// primes
// arithmetic sequences +/- k
// geometric sequences * k
// div sequences, mod sequences
// squares, cubes, etc.; "simple polynomial" sequences of n^k
// more complex polynomials
// multi-variable polynomials
// "polynomials with memory"
// recursive equations (themselves possibly polynomials): Fibonaci, factorial, ?? etc.
// any "property function" from known branches of mathematics -> this opens the discussion about "sequences and sub-sequences" (*!?)
    // <e.g.> any sequence of "special primes" is a sub-sequence of the sequence of all primes
// harmonic series somehow mapped to integers
// pseudo-random generators (a great source of patterns, and they are ~ "instantiatable by seed")
// "div, mod, offset, shift, ?? etc." functions
    // <e.g.> there is that function that produces sequences that always terminate with a certain periodic sub-sequence [there's an (unsolved) mathematical problem about it]
// cellular automata -> a very big search space (the rules are themselves likely a function space to search in; and it's interesting to note how a function space is the
    // parameter space for the cellular automata; but the general framework is such that each cell is parallelizable in computation ! so I do not know how does that affect
    // the function spcae being used as a parameter space ?)
//


#endif // SEQUENCEGENERATORS_HPP_INCLUDED
