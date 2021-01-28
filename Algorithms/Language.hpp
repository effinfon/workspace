#ifndef LANGUAGE_HPP_INCLUDED
#define LANGUAGE_HPP_INCLUDED

/// TD
/*
    "intermediate, abstract assembly language": addvec512 -> machine assembly language
    (*?) a runtime type system would actually be useful, not just a static one; also, for better integration, there should be
        an "informational continuity" from the static type checking to the runtime type checking
    @~ 5:26 https://www.youtube.com/watch?v=DnT-LUQgc7s
        (*?"") "these are mechanisms that allow you to write really nice code even though you are using types for everything; so
            the types do not get in your way as enable you to do things"
    (*?!) "zero-cost abstractions"
        // "whereas in ... many of these abstractions are zero-cost, they are `compiled away`"
        // "at runtime runtime is as if the abstractions are not there, but you can still use them in your code"
    "the *.wat file is a human readable format similar to assembler files. it is then converted to a byte code which then is the (virtual) machine code. similar like assembler text files are getting converted into native machine code of a certain cpu/mcu"
        // the consensus seems to be that .wasm stands for "WebAssembly assembly (code)" (there is overlap in the name though)
            (this should be a kind of binary code), whereas .wat stands for "WebAssembly text (code)"
    (*?) I like Rust's help system which offers suggestions in the compiler; but, I do not like the "prefix with _ if this is intentional", because it doesn't help the
        compiler to understand why I did it; and maybe what I did is not necessary
        // (*!?) specifications need to be "minimal" (?!); this is an essential aspect of specification languages and programs written in them (!)
        // (*?) there are "explanations (and examples)" for the error codes that the compiler produces (or well, for some of them, which are fit well to being "explained" like that)
        // (*?) they seem to even have github issue #number in the description string from the error helper
    (*?) the essence of these languages are their type system; the functionality that is implemented in them, though, should not be made mandatory
        as per the design decisions of the inventors; instead, a good typed language would allow itself to be (easily) (re-)programmed by the programmer
*/

#endif // LANGUAGE_HPP_INCLUDED
