#ifndef MEMORYSYNTAX_HPP_INCLUDED
#define MEMORYSYNTAX_HPP_INCLUDED

/// TD
/*
    (*?) std::move -> dynamically linked -> dynamically extend or regress a stack, based on run-time behaviour of std::move; the point is to imagine having a scope, then
        having a function call being done (which returns an std::move, thus the stack would either have identified this call statically, or would have to deduce it dynamically,
        case in which it would need to do a ~ "scope's stack extension" and after that effectuate the function call)
    (*?) how does the stack memory allocation differ from the heap memory allocation (?)
*/
/*  QUOTES AND DISCUSSIONS

    "In a time sharing operating system, we we will need to allocate the system's memory among multiple processes. Moreover, we may need to deal with situations where we do not have enough physical memory and have to swap chunks of data between memory and secondary storage (disk). Systems in which we move (swap) entire processes between disk and main memory during execution are called swapping systems."
    "There are a few problems with static linking. One is that if a library changes (due to a bug, for example), then the version in the executable file is outdated. The second problem is that because many programs have a copy of common library elements (e.g., printf), the size of every program file is that much bigger. This is also reflected in the executable process: even if multiple processes use the same code, each must have its own copy. The desire to remedy this led to dynamic linking and shared libraries."
        // (*?) this is suggestive; what about doing this at the level of a whole codebase (and even when merging codebases, at a system-wide level) ? but isn't it something that already happens
            when deciding how to modularize code into "interfaced scopes" / "program functions", or when to inline a program function into another, etc. (!?)
        // (*?) also, libraries are essentially source code that's been translated; whether it be static or dynamic is but a problem of reusability and modularity (!?), and this problem gets
            to be solved at multi-scale; all the usual discussions are focused on the "program level / scale", whereas I desire a "system-wide scale"; otherwise, the only reasonable argument
            for not using static libraries is that it does not require recompiling in order to change the version of the library; (*!?) this shouldn't be the true problem though, and this
            leads to another important discussion, about "modularity of updates" -> files, executables, libraries, linking, memory segments, program functions... all these concepts are nice, but
            are just the current design's implementation concepts; I desire the general optimization problem that makes decisions at the system-wide scale; that way, if I need to update just a function
            in a program, I can do that without recompiling the whole program; but this effectively leads to the idea of breaking up the program into many objects that get linked at load-time; it suggest
            moving (almost all of ?) the linking part of the compilation to load-time, allowing for faster updates, with less overwrite, but also a more modular update; but imagine, if updating a function
            opens up the possibility for more integration with another set of functions, then those too need updating; (*!?) then, if some of that optimization has to occur at the level of linking, then
            that keeps occuring repeatedly at load-time => a problem of more efficiently using (pre-)compute
            // (*?) thus, the current practice of things is a balance between what gets statically linked (well, effectively a large part of the program is "statically linked"; just look at all the
                functions a programmer writes, the structs, all the .hpp and .cpp files, etc.), even "static libraries" (I do not know why they are separated into static and dynamic libraries, when
                they should be the same file format, either to be merged into the program or to be load-time linked to it); it seems to be more of a "division of responsibility (among programmers)"
                whenever a (codebase -> binary library) is considered a dynamic library
            // (*?) the more relevant perspective would be: in the editor, one can markup parts of the code which are likely to change in the future, so they can be dynamically linked, whereas the rest
                can be statically linked; next, from considerents of code reusability: I do not see the "dynamic library" mechanism as being "strictily necessary" just to implement code reusability,
                as in when multiple programs run that use the same code and could just like to each other's code, but I guess it does make it easier to manage explicitating which parts are "dynamically
                shared among programs (and processes)" (but then there is the overhead for monitoring shared libraries, which could likely be dynamically reduced by a "transform" which would occur at
                run-time; such mechanisms give the system more adaptivity capability, to switch from more consuming periods to more efficient periods depending on available resources, to introspect
                and adjust parameters or code, ?? etc.)
    "Dynamic linking does not solve the issue of every process' use of a library consuming system memory. If twenty processes each use the printf function, each one will have its own copy of the code that implements it. Shared libraries add text (code) sharing onto dynamic linking. If a program needs to use code from a dynamic library, the stub function checks whether the needed library component is in memory. If not, the stub requests that the operating system loader load it. As with dynamic libraries, the stub is then replaced with the address of the library. If the shared library is already in another process' memory, the operating system creates a read-only shared memory region among the processes so that each process will have that code in its address space."
        // (*?) apparently "dynamic linking (/ dynamically linked library)" does not imply "shared library"
    "To share this memory among multiple processes means that we will need to reserve a region of memory for shared libraries. Because different libraries may be loaded in a different order, we cannot predict what specific location a library will be loaded into. For this reason, it is important that shared libraries are compiled with position-independent code, containing only relative memory references instead of absolute addresses."
    "Giving the machine to one process and keeping just that one process in memory does not work if we want to run multiple programs concurrently. We really wanted to have the illusion of running multiple processes at once and provide users with interactive response to processes. Swapping an entire process between memory and disk each time we context switch would be prohibitively expensive (disks are insanely slow compared to memory)."
        // (*?) this suggest yet another possible optimization problem, namely about how to decide "context switches" (?!); but what is there to decide about them ? there's essentially the "process",
            with its resources and computational time (assigned by the scheduler, probably according to "priority"); "swapping the whole process" seems unnecessary, but it could be that knowing exactly
            how much to swap each time is what can be optimized; for example, if the other process is in a loop that can be estimated to last for another ~ 476 "context (switch) cycles" / "schedules"
            and there is a rather limited ammount of necessary "spatial scope", then there is little to switch (as a contrived example, maybe only some 5 integer registers are needed, 2 vector ones and
            1 float register; so in principle the others could remain unchanged, or preemptively prepare for the next expected context switch); essentially, the optimization is likely about "predicting"
            and about "limiting necessary change", and these will allow for doing things preemptively [but in parallel to the context's actual execution, which could impose more complexity on the hardware (!?)]
    //
*/
/*  DISCUSSIONS

    (*?) "run-time independent, static stack structure" -> although the input might vary (if there is input required at all), the program can be statically proven to have the
        same stack structure in all of its possible executions (the discussions ommits at this point whether the program cannot effectively be pre-computed as a whole, which it
        can in those cases where it has no dependency on "outside" input)
    (*?) -> "static stack programs" vs "(non-adaptive) dynamic stack programs"; and further, "dynamically adaptive stack programs"
        // specifically, non-adaptive stack structures would be those where the flow of function calls is dependent on the input (and thus dynamically determined), whereas
            adaptive stack structure would mean that the structure of the scopes of function calls can actually change at run-time [~ self-modifying progarm (*?), but is it
            limited only to this ?]
    (*?) why is a limit implemented for the stack-depth ? how is the stack allocated for a process ? does it allocate an estimated ammount of needed run-time memory, which resulted
        from a sort of (?"program analysis in dynamism"?), where the compiler would execute the program and search its space of possible states and estimate the interval of memory used
        at run-time (?); or does it just allocate some fixed value, and then as more memory is needed it actually calls upon the kernel to assign more memory pages (?) [just like with
        the heap essentially, but maybe the fragmentation or allocation is done differently, because the ordering or some property is different from the heap allocations (?)]
    (*!?) imagine and discuss: "the stack seen as the ~ `memory expanse` needed for a function to compute" (!?); in practice, this is extended with the return address and the overhead
        needed for function calls
    (*?) how does multi-threading interact with the abstractization of stack memory (?!)
    (*?) how does "stack collision" occur (?)
*/
/*  LINKING

    (*?) a program is compiled into a "position independent code" (PIC) format, then when it is loaded into memory, the relative positions get computed and are loaded into memory with the actual
        program, in its "final / executable form"; from there on, programs should still be able to ~ "mutate" or move around, ?? etc.
        // (*?) for example, imagine compiling the whole operating system and other used programs, all together in a single program; but then a concept similar to "linking" could be used,
            but more as a sort of "dynamic adaptation" that can occur, in response to "plugging in or out, parts of the program"; there's also consideration to be had about redundancy
            and robustness to when a part of this monolithic system could fail, and how to effectively teach the program to self-modify, to "reload sort of hard-linked parts of itself",
            or to "reset the state of hard-linked parts of itself", or rather how to "`soften links` dynamically, then plug out the errored part(s), plug in the `reset state` or
            `last stable or valid state` variant(s), `harden the link(s)` and continue execution" (!?)
        // (*?) therefore in essence, a sort of "dynamic, adaptive linking state" ("softer" and "harder")
    (*?) "modularity" -> linking needs to also be discussed from the point of view of modularity; parts of memory can be shared as "shared code and shared read-only", some are "shared
        buffers" [with possible rules for the order in which "control flows" can read or write (*!?); "control flows" can be extended to "threads" as well]; so "code reusability" is
        an aspect of linking, "memory sharing" is another [and its usefulness in "synchronization" of control flows (and threads)], ?? etc.
    (*!?) static linking and dynamic linking -> this decision problem needs to be automated, it's unpleasant; well, that's a bad wording; rather: "it can be handled better by being specified instead"
    (*?)
*/
/*  LIBRARY MANAGEMENT, LINKING

    (*?) identifying and referencing libraries that the executable needs to link to when loaded:
        (i) use a filename (or even "path filename") to identify the library (could also be used together with the $PATH$ environment variable of the system)
        (ii) use hashes and uint64_t length to identify the library file with which to link
        (iii) ... ??
        (iv) (*!?) use a specification [discuss this from a perspective similar to compression - index spaces - data type's space; in the sense that, one guaranteed way to "specify"
            a library to link is to basically have an index equal to the data type's size of the instance, basically a "copy" of the library itself (note: it could also be a permutation
            of the same length); but if a specification is used, how does that correlate with it being basically a sort of search problem (and / or optimization problem ?) and to what
            degree is it a compression, or the uniqueness of the solution, what to do about there possibly being different versions of implementations for the specification, should there
            be both a specification and an optimization being explicitated, ?? etc.]
            // the point here is to create a more "agnostic mechanism", as opposed to having to know the names of the libraries (which is much less related to what the library actually does
                and the programmer might be "locally aware of"; it is undesirable to have to search documentation for the name of some file, which might change with time, or whose changing
                for better performance or consistency might be impeded exactly due to legacy code compatibility which searches for a specific file name, instead something more "malleable",
                like a specification); a specification can remain the same and its implementations change with time, but the source code would not need any changing; there's another advantage,
                namely that specifications are sufficiently abstract (or should be !) that no change in paradigm or ?? etc. will affect the performance of the program, instead the implementation
                search (and then optimization search) will still find the required source code / binaries / ?? to be "linked" with (*!?) [actually, this needs further discussion, because
                this is actually wrong; it's just that abstractization cover "more layers" and this makes them ~ "less vulnerable / in need of adaptive change" to small details, but that doesn't
                make them impervious to change, only more robust ! therefore, there would be possible changes in paradigm, or due to hardware changes or different sub-spaces of complexity space
                that would lead to the even the specifications (basically abstractions) to be ~ "outdated"; the desire being chased here is that of ~ "permanence of definition", just like with
                mathematics; but even in mathematics there are things which get replaced, and then otheres which are ~ "evolutionarily conserved", therefore it suggests that depending on the
                sub-space of the complexity space one explores, abstractions themselves have different ~ (?"robustness" / "extents"?)]
            // (*?) to be found, implementations for specifications would be better suited as being part of the memory of the machine that is the specification searcher; the ideal would be to
                have the implementations of many programmers stored (compressed) as solutions in this searcher's memory, and said memory to effectively be a sort of "points in the search space",
                but from which the searcher can always derive other points; points act as "starter points" or "precompute" or "help" for the searcher, but the searcher can also search without
                needing memory, it would just take longer to find solutions on its own
                    // (*!?) another usage for the specifications searcher would be to find the more robust implementations; one could start from a dataset of implementations for a specification
                        and have the searcher analyze how well they conform to the specification; it might simulate security attacks and identify vulnerabilities, then select parts of code which
                        are more robust and secure; so one objective would be to crawl the internet for source code and to automatically process it, producing programs as per specification, but
                        which also automatically makes use of the years of effort of other programmers in making them secure, robust, efficient, etc. (!?), with the added mechanism of the searcher
                        itself running its own security simulations and doing efficiency optimization (!?)
                        // (*?) reinvent the wheel, but do it automatically, and have a way to improve on it adaptively, dynamically; adaptive code is the future, specifications and dynamic optimization
        (v) ... ??
*/
/*  HARDWARE-IMPLEMENTED MONITORING

    (*?) hardware interrupts, setting "memory protection areas / intervals" and triggering "unauthorized memory access" errors
    ...
*/
/*  MEMORY PARTITIONING DESIGNS

    (*?) Single partition, monoprogramming -> so supposedly this is a case where the BIOS is loaded into memory, it boots the OS which is also loaded into memory, and then
        another single program is loaded into memory; (!?) the question is "where is the border between a program that can be statically predicted in a single-partition memory design,
        and a program that grows sufficiently big that it cannot be reliably predicted anymore, and to some degree its correct execution is left to chance ?"; this questions tries to see
        this design from the perspective of two (or more) "very small programs" as opposed to a single program (which is essentially composed of those smaller programs); therefore, what
        constitutes "a single program" and what constitutes "multiple programs", but not from this arbitrary perspective of "it's been compile that way", but from an abstraction's (yet
        unidentified) perspective the relates to (maybe) the predictability of the program's use of memory (and of its components' use of memory !); to find the abstraction, search around
        the cases of: "if one loads multiple programs, how and when does the management of those programs coincide with that of a single program (?), and on the other hand when does it not (?)"
        // (*?) what if it were a multi-threaded single program, on a monopartition of memory (?)

*/

#endif // MEMORYSYNTAX_HPP_INCLUDED
