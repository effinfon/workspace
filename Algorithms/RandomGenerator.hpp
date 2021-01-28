#ifndef RANDOMGENERATOR_HPP_INCLUDED
#define RANDOMGENERATOR_HPP_INCLUDED

#include <random>

/// TD
/*
    the "randomness" of these generators is in their dynamics; as such, if the system gets restarted every time the program instantiates,
        the system won't produce randomness effectively, but instead keep restarting itself (well, its sequence); thus, save the system's
        state in a file and read it at the next instantiation of the program, so that the sequence will  continue even across program instances;
        somehow handle multiple program instances executing in parallel and still ensuring each other's sequences different (?!)
    a ~ "format string"-based query to the randomness generator (albeit, also offer a selection of possible generators, a string presentation
        of their parametrization, the seed(s), etc.

*/

    // (*?) how to set its internal state though (?); I cannot read / write the generator's
        // state fromto a file if the internal state is unaccessable

// static std::mt19937 rand;

#endif // RANDOMGENERATOR_HPP_INCLUDED
