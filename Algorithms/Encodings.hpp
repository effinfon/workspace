#ifndef ENCODINGS_HPP_INCLUDED
#define ENCODINGS_HPP_INCLUDED

///
/*

    search for optimal encoding, based on specification / requirements / constraints
        <e.g.> for encoding a specific kind of text, a set of characters are needed; and then some special characters
            for ~ "signals" or "context", etc.
        <e.g.> an encoding used for text and mathematical character sets (and maybe additional data, such as subscript or superscript, bold or italic, etc.)
            // so what would otherwise be done by ~ "specific sequences of the basic characters" could instead be done by ~ "state characters"
        <e.g.> optimize for upper case -> lower case conversions and verifications (so optimizations not only from the perspective of storage, but also
            from the perspective of performance at run-time, of the time it takes to do (possibly) "intense computations"
        ...
    ...
*/
/*  ENDIANNESS

    (*?) I see, it's to be seen as the "end of a written number", "not the end of the data instance, as an address"
        (the end would be the higher address and the start would be the lower address); I guess the people who have trouble
        remembering it are those who should think of it as "startian" instead, because they're thinking of the address

*/

#endif // ENCODINGS_HPP_INCLUDED
