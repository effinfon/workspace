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
/*  DISCUSSIONS

    (*?) bilateral arithmetic -> <e.g.> being able to get the LSb 3 bits or the MSb 3 bits, or 5 bits, or n bits in a similar fashion to (x % 2^n)
*/
/*  COMPUTATIONAL COMPLEXITY -> ARITHMETIC

    (*?) "analog" as in "physical analog" [in reference to "analog" and "digital" -> (*!?) communication, and then computation (the two are considered separetly)]
        // "digital logic" and "analog logic" -> computation
        // "digital representation" and "analog representation" -> communication
    (*?) but supposedly the brain would be a digital communication (I take it they mean polarized-depolarized as being the binary state ?) and analog computation [the
        physical equations that drive the behaviour of the components, resulting in current flows (*?)]
    (*!?) is there an advantage in implementing "analog switching logic" ? (actually, just discuss it; but consider things such as "switching hysteria", or ?? etc.)
    (*?) the speaker claimed that neurons talk mainly to influence each other's "probabilistic distribution"; the interesting note though is that neuronal networks
        are affected by thermal effects, which can close / open gates which "should otherwise be" opened / closed; what I need is the abstractions for a model that is
        resilient to "thermal noise" (for both digital circuits, and analog circuits, be it communication or computation); then continuing from that, to start the discipline
        of "probabilistic circuits", then further, to discuss about the subset of "self-entraining probabilistic circuits" (and possibly other property circuits subsets)
    (*?) consider the problem of: "analog means of doing your computation"
    (*?) the speaker in https://www.youtube.com/watch?v=vHlbC74RJGU claims that analog computation is more advantageous, and then that digital communication is more advantageous
        // @~ 12:24 (*"") "the brain system uses analog for computation because analog degrades more gracefully with noise; so when I have this kind of stochastic swtiching happening in
            the ion channels all the time, I can't rely on 0 and 1 and that kind of thing"; then goes on to exemplify <e.g.> consider how signals add up in dendrites, as analog
        // @~ 13:15 (*"") "but analog is not good for communication, .... susceptible to noise, so the brain uses a digital representation, the spikes, to communicate their results";
            "and, you know, in digital, we all know, communication is an identity operation, so by using error-correcting codes, the way we encode information, we can correct more
            errors"; the speaker seems to suggest that error-correction is "easier" in a digital system than in analog (I think not, but the mechanisms used by spacetime is too complex
            to have been already discovered by brain design ?)
        // @~ 14:24 -> a video [inside a video] of the signal spike's propagation; note the "ionic gradient" which builds just outside the axon; the speaker claims "that happens in
            aboout 1 msec"
*/

#endif // PROCESSORARITHMETIC_HPP_INCLUDED
