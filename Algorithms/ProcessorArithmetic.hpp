#ifndef PROCESSORARITHMETIC_HPP_INCLUDED
#define PROCESSORARITHMETIC_HPP_INCLUDED

/// TD
/*
    (*!?) in here one needs to visualize, explicitate, verify, etc. the correlation between a "type" and the "computation on the processor",
        because it is often the case that I wonder how exactly / where exactly the "linking" betwen a "value", which gets "cast into a type",
        and the operation done on a processor, actually occurs (!?)
    (*?) (abstact) logic (abstract) circuits [what exactly can be abstract here ? the process that implements the logic ? yes... it's rather
        "strange" to think how some, or even ~ "any" (given certain abstarct properties) physical phenomenon of some kind can basically be
        (?"the same"?) as the logic of arithmetic; next, the "circuits" used to describe the logic, or rather whatever the syntax for the chosen
        logic might be, as there can be multiple logics chosen (from, or even simultaneously used) and each logic can have multiple representations,
        of which "circuits" are (*!?) "a" typical representation (?); so what is an "abstract circuit" then ?]
        // (!?) whether it is a "complete translation" or an "emulation" -> infinite polynomials, without an "analog", their complexity map
            actually goes to infinity... that is usually ~ as there being a "space break / gap", so there is actually no path between the points
        // essentially, TD: devise representations for logic, and search for their implementations <e.g.> define addition on 8 bits, multiplication, subtraction, etc.
    (!?) a binary view of the registers would be needed, to visualize the arithemetic as it occurs, step by step
    ...
*/
/// TD optimization
/*
    identify operations that are "independent"; next, if they are < 64 bit, try to have them execute in the same register, in one operation
        (*?) warning: depending on the instruction, it might be the case, for example addition, the overflow-carry of the LSB will flow into
        the MSB (!)

*/

#endif // PROCESSORARITHMETIC_HPP_INCLUDED
