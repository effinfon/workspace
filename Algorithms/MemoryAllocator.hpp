#ifndef MEMORYALLOCATOR_HPP_INCLUDED
#define MEMORYALLOCATOR_HPP_INCLUDED

/// TD
/*  TERMINOLOGY

    allocator
    collector
    mutator
    ...
    heap -> break (~ kernel-imposed boundary)
    system call -> trap (and a context switch from user mode to kernel mode; a dump of the register file as well; also, I'd assume that not all context switches
        are really from user mode to kernel mode, but also from kernel mode to kernel mode; but what about user mode to user mode context switching ? does context
        switching even occur without kernel mode ?)
    ring allocator, frame allocator, static allocator
*/
/*  FUNCTIONALITY

    (*?) alloc -> extend alloc (if possible) [very useful for certain cases]
    static allocation, dynamic allocation, stack allocation, heap alloaction (*?)[heap- vs stack- reserved memory allocation]
*/
/*  SAFETY, SECURITY

    memory barrier
    memory access error, out of bounds memory access, unauthorized memory access [authentication, authorization (*?!)]

*/
/*  DISCUSSIONS

    (*?) having a (fixed ammount of) stack-reserved memory; it can be (only ?) "forward-shared" to ~ "future / further scopes" on the stack;
        it can also ~ grow by having another scope allocated a big ammount (probably a templated function scope ?); actually, these should be
        JIT-able (?!), with some sort of "run-time template programming and JIT" (*?!)
    (*?) "general-purpose memory allocator" -> what would a "specialized-purpose memory allocator" imply then (?)
    (*?) "critical section code" [and its accessing under a lock, in single-threaded mode basically; it doesn't have a robust variant that runs in parallel (*!?)]
    (*?) memory allocation in the context of multi-threading -> multiple (/ simultaneous) allocation calls, allocating shared memory, "memory thread-groups" (*?),
        "thread private memory, allocation" (for example, even if the thread is part of a bigger program, it can still have its own private memory segments), ?? etc.
    (*?) a variant of malloc that can run robustly in multi-threaded mode as well (essentially, the multi-thread variant can run robustly when there is lots of available memory,
        but will become unstable and error-prone when little memory is available; it could even deadlock probably); thus, it needs to dynamically go from a multi-threaded code mode
        to critical code mode (/ single-threaded code mode), depending on the ammount of memory (!?); besides, the "stable" multi-threaded version would likely become less performant
        and essentially converge to the complexity of the single-threaded mode (*?)
    (*?) parallel variant of the "memory segment-fit allocation-searcher" (?)
    (*?) when allocating memory, depending on the type's introspection, there might be alignment details to consider (?), does malloc() handle the padding bytes ?
        // (?) apparently malloc() and calloc() (?)[what is calloc() about ?] only receive the sizeof(T)
    (*?) memory model: static-bss-etc.(fixed size), heap (growth direction 1) ... (growth direction 2) stack, (here there could also be another set of fixed-structures)
        // (*?) but what about limiting the size that the heap can grow (at least for a single process) [actually I found that this is called a "break" in UNIX parlance, but it can
            be "moved" by requesting more memory from the operating system], and then it would effectively start returning malloc() errors due to insufficient memory -> the program
            would have to handle those
    (*?) what is the size of a "page" / "cluster" / "block" of allocated memory (?)[it would seem to be decided at the level of the kernel, nad might have a size of approximately 4KB];
        I suspect that malloc() has to effectively handle the "to whom was X allocated ?" problem, just like filesystems have to; thus, to reduce the ammount of book-keeping
        it has to do [the problem of "required tracking-metadata vs actual memory being alloacted" (*?) -> (*?) the 1:1 ratio is the worst case for the cost of tracking memory alloaction ?]
    (*?) "internal fragmentation" and "external fragmentation"
        // apparently, the "break", or the "upper bound of the heap memory" can be extended (and I suppose shrinked as well), so a discussion appears: "whether to request for an extension
            of the heap memory, or to try to find something inside of it
        // (*!?) another interesting operation would be to "defragment" the heap (this likely does not generally get implemented), but it would require retransmitting
            the new pointers to all the threads that have requested memory from the allocator => temporary stop of the threads [this could somewhat be optimized,
            for example by doing it "unsafely" in a period that is "known for the threads not to be heap-memory critical", thus since they won't use the pointers they
            can be "safely" moved (safe by virtue of the dynamics at a higher level, not strictly at the interaction of the interface between the threads and the allocator)]
    (*?) in some discussion(s) above there was a slight description of what would otherwise be "memory pages, like the filesystem has to do; all for the purpose of tracking
        memory allcation", and apparently the kernel manages that actually; (*?) what I wanted to point out was that, when requested for more memory, it allocated memory pages to
        the heap, in some particular order, and it actually has to make use of the memory management unit (MMU) module of the processor to "virtualize a contiguous memory segment"
        for the threads (!?), because the memory pages themselves are actually not contiguous in the physical memory
    (*?) the cases when the kernel has to "write to disk" memory pages that "are unlikely to be reused soon" (!?); using the function "longest time interval since last accessed"
        is not optimal; "dynamic analysis over the lifetime of the program" and "system-wide integration of program, memory usage analysis" could find much better patterns (!?)
        // (*?) there is an associated discussion here, namely that processes might deadlock in the disk IO (!?)[I wonder if they really deadlock, or just move extremely unperformantly]
        // (*?) so effectively, when the kernel runs out of memory pages, there already occurs a phenomenon of  "pointer collision"; but the aspect to note is that it actually doesn't
            "really" occur, because there is still the indirection of the MMU; different processes's pointers do not collide like that; but how do they collide then (?!), especially
            when a process intently causes a memory buffer overflow, to what memory does that gte access to then ? or is it only memory from the same process ? can it be from other
            threads ? could it be from the thread of a different process ? does the MMU work over processes, or over threads, or something hybrid ?

*/
/*  IMPLEMENTATION CASES, DISCUSSIONS

    (i) so, the segments are, let's say 64B long (?), and they get to be allocated; but then, consider alignment;
        inside one of these pages, there are multiple ~ "starter points" which are "aligned memory points / addresses";
        from those starter points, an allocation segment extends that needs to be able to include the sizeof(T); this might extend over multiple pages though;
        also, the sizeof(T) needs to be allocated onto a contiguous memory segment [otherwise one would incur the overhead of having to keep track of which
        allocations are contiguous and which are not, and if they are not contiguous to keep track of all the pieces; next, it would force the design towards
        having to call an indirection for retrieving memory, which would involve the "memory allocator's tracking system", which is solicited both by read requests
        and write requests for new alloactions and deallocations (thus a parallelization bottleneck)]
    (ii)
*/
/*  DISCUSSIONS

    (*?) "lifespan / scope": when used for "automatic variables" (or "scope local variables"), if the memory is allocated with use, then automatically delete will be called
        at the end of the current scope; but, if it is a member attribute being set, then delete will be called at the "end of span / scope" / destruction of the object (?)
        // actually, I suspect that i missunderstood something about new, but still think that id calls delete automatically in certain cases; or could it be that I really
            need to manually call it (be it in a local scope or in the destructor); could it be that essentially I was under the impression of automation, when all it was
            is due to the ~ "destructor memory management" which itself calls delete, and can handle memory deallocation for structs / classes, but still leaving out
            primitive types which do not have a programmable destructor (it is compiler built-in) (*?)
*/
struct MemoryMap {


};

#endif // MEMORYALLOCATOR_HPP_INCLUDED
