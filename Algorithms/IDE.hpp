#ifndef IDE_HPP_INCLUDED
#define IDE_HPP_INCLUDED

#include "Codeblocks"

/// TD
/*
    (*?) imagine visual studio's right-side ~ "column of code"; now imagine a "graph style, code-space viewer"; the point is to see whether
        a codebase visualization is feasible which is not so "linear"; the point would be to also arrange the codebase in a "non file based architecture" (*!?)
    "code hiding" -> as with comments (a modification of color, but also of transparency !), so color palletes and transparency, the possibility for ~ "transparency
        inversion" between source code and comments and vice-versa, ...
    dynamic "jump to code"; usable (especially) in the TODO lists, but it should be a "general feature" (usable "anywhere else" in the IDE, as well)
    there is an essential problem with "pointer syntax" vs "reference syntax" (which up until now I have not yet understood) vs "?usual / integral? syntax" [which is
        // "as if you're operating with the values in memory, and not with their addresses or their references" (whatever the difference between those two might be)];
        // thus: a digramatic representation that "digs through the type of a variable / a `memory instance`" (or its ~ "structural hierarchy"), and clarifies to the
            programmer, in a visual manner, what the structure / hierarchy (pointer wise, reference wise, value wise, etc.) is [including whether it's stack allocated,
            heap allocated, or ()]
    ~ "auto-adjuster of indentation", dynamically intervening (or a sort of "indentation style maintainer"); especially useful when modifying code, at the level of
        control structures <e.g.> @~ 15:00 "Default values, explicit uninitialization (part 1)" - Jonathan Blow
    a "delete whole line" and a "delete all to the right of the cursor, on this line" (same video reference as above; very useful)
    (*?) a macro processor and a template processor, being aware of strings in a functionally complete way, and being aware of types in a convenient way; I think the two
        are useful merged; also, the macro processor is likely the superset, whereas the template processor is a subset of it which abstracts a lot of complexity
    search for all the occurences of something (and optionally automatically put a breakpoint on those lines where it is found)
    line numbers need to be displayed; errors, warnings, questions, etc. which have knowledge of the file-line number-column number need to be able to jump in-code
        exactly at those places
    (*?) what about errors / warnings / questions which can be more "vague" and only deduce a general are in-code / scope where the phenomenon occurs (?)
    (*?) search in a file, search in a pre-made list of files, search in the whole codebase, search across multiple codebases
    (*!?) given the objective of system-wide integration, it is the case that at some point it will be required to "merge / integrate multiple codebases", thus
        similarly to how git produces conflict reports on mergers / joins (or whatever they call them), so will the codebase merger [except it's likely a problem
        of greater complexity: (i) possibly multiple languages that all have to be translated to "the language"; (ii) resolving the dependencies of each codebase;
        (iii) compatibility of the codebases as source code (they might work fine together / be compatible as compiled programs, but that does not imply that their
        source codes are compatible) (*!?); (iv) reverse-compiling / decompiling libraries (into "the language"); (v) etc. (*?)]
    move the cursor to the top / bottom of the current function, or of the current scope, etc.
    (*!!?) not everything that does a specific thing has to be a function (especially because then there's additional structural complexity in indirecting everything); so
        what I desire actually is for the IDE to provide a mechanism of effectively "collapsing selected code" and allowing me to explicitate a specification for that
        selection; that way, code can be written even in large functions which will be "re-describable abstractly" (by this ~ "collapse and replace" mechanism) and even
        be verified for correctness according to the specification {locally define a ~ "interface" and the domain for the interface, and then the outputs can either also be
        explicitated element by element (or "case by case), or if a ~ "compression" [or "feature", or "AI filter", or "(learnt) abstraction by ML", etc.] is known then
        a specification can be explicitated}
        // the point is that this could greatly increase the speed for debugging things, and the specification and checks (otherwise called the "tests") do not actually
            have to be deleted afterwards, and can probably even be reused (!?)
        // (*?) yet, another discussion has to be had about "code reusability"; since some sort of "in-scope interface" is being defined for the code, and an analysis is done about
            what "out of scope (dependencies)" it has, it can thus be verified where is it eligible for it to be reused, it can be given an identifier [of sorts, maybe in a
            different list (*?)], etc.
    typo checker (?) [I don't want ti to pester me about where the dash '-' is placed though, only about the words themselves being correct; what this means is exemplified by
        "take-down" - I only care that "take" and "down" be correct]

    ...
*/
#endif // IDE_HPP_INCLUDED
