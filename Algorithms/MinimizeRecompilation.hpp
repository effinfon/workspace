#ifndef MINIMIZERECOMPILATION_HPP_INCLUDED
#define MINIMIZERECOMPILATION_HPP_INCLUDED

/// TD
/*
    and how exactly does the Makefile know that an object file is up to date
        with the source file and doesn't need to be recompiled, if it doesn't
        even keep a hash of the source file used to compile the object
        file (?); basically, it doesn't, it simply assumes that no modifications
        are made to the source files, and do not solve the problem, in essence,
        except for a few use cases
        // apparently it does keep track, supposedly using the timestamps (but I think
            it compares the *.o's timestamp and the source file's, thus effectively
            keeping no metadata about the files (interesting, efficient, but robust enough ?)
            // well, it would fail against object files which simply have the right name and
                have a timestamp greater or equal to that of the source code file
    how does Visual Studio typically fail to compile object files that are not up to date (!?)

*/

#endif // MINIMIZERECOMPILATION_HPP_INCLUDED
