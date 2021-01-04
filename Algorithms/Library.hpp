#ifndef LIBRARY_HPP_INCLUDED
#define LIBRARY_HPP_INCLUDED

#include <filesystem>
#include <string>
#include <fstream>


/// TD
/*
    searches the whole filesystem for files which might be my notes (they are all just text files)
        // maybe use a keyword based search; these could be obtained by frequency analysis from files that I already
        know are my notes
    compiles them all into a structure where I can see them all at once, or maybe a graph, or maybe a ~ document distance visualization


*/
/*
    design a database model (content-search, similarity-search, continuous merging of content, semantic analysis, etc.)
        for the notes; it should be able to integrate text, audio, images, video, plots and formulas (ready to be computed or pre-computed
        or even adjustable; it might even have a pre-computed case and allow for the computation of another, which could be subsequently added
        as well to the list of pre-computes, etc.), it should be able to contain source code (and then there's the details of how I'd like to
        format and present the code and annotate it, etc.), even add executables / binary files (mainly as reference, but also to be executed
        in a sandbox)
    it should be able to store codebases, for example the one for Windows XP
    (*?) indexing -> title search, content search, parallelization of search on ~ "local memory blocks" [exhaust the memory input by efficiently
        using cores; then it becomes a matter of how much the IO itself is parallelized; for example, the PCIe 3.0 / 4.0 could have some ammount of
        bandwidth, which would be more or less utilized fully by the SATA 3.0 connections; this implies using multiple SATA SSDs and having the
        content be distributed amongst them, such as to try and maximize the "distributed bandwidth" for all use cases of interest (this could imply
        simulating the filesystem in RAM, and profiling the use cases of the files during actual use, and then writting it to the non-volatile memory);
        this also implies the possibility of utilizing multiple PCIe 3.0 / 4.0 channels for interfacing non-volatile storage with the processor(s)]

*/
/*
    (*!?) compression... global compression seems very good, but it poses a problem with the "SSD's write-wear life"; so instead, one could
        use ~ block-based compression with sufficiently big blocks; but even those are inefficient when it comes to "diffs"; there is also the
        problem of, otherwise using a ~ "incremental compression", where the dictionary grows and the newly added strings make use of the best
        compression, but even so, when something previously compressed needs to change, one could use a diff file and link that (in a more dynamic
        area of the SSD, which is less compressed probably, and actually does change more), but then there's the discussion of very long chains of
        diffs (?!); besides that, if a 3TB file needs to be accessed, and is made of many diffs like this, just how inefficiently will it be used
        given that it would constantly get read in pieces and modified and then read with another diff, again and again (?)
        // specific use cases: storing a database of articles / notes / books, or a codebase
    (*?) initially, design a ~ "featureless filesystem": no folders, just files; no paging, instead just a pointer and a length [use the ~ (?"stack and heap
        architecture"?), or ~ "2-boundary growth architecture"; meaning that at one end is a growing table of pair<pointer, size> and at the other end
        are the files];
        // (*?) what about ~ "partial files" (?), which are spread across partitions, or even just being made of multiple files in the same partition (or both,
            multiple files on possibly multiple partitions)

*/

#endif // LIBRARY_HPP_INCLUDED
