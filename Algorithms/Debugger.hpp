#ifndef DEBUGGER_HPP_INCLUDED
#define DEBUGGER_HPP_INCLUDED

/// TD
/*
    (*?) first of all, change the terminology; running a program in ~ "in-detail inspection mode"
        does not necessarely mean that this is done in order to find bugs correct any such bugs
    load source code into the "context" / "model" / "framework" (~ proof system's "context"), then place
        a cursor anywhere in the code and tell what symbols / identifiers should be "visible" at the point
        in context
    breakpoint mechanism -> into the source code at different levels
    multi-language, in parallel, source code visualization: this means that one can view the source code in C/C++ and
        in the intermediate language(s) and in the assembly language and in machine code, all in parallel; also, a breakpoint
        can be set in any one of these and they all need to work together
    indicate lines that have been executed in the current scope by highlighting them (say, with yellow), so that it is intuitive
        to figure out whether the arrow at the beginning of a line signifies a line that "is about to be executed" (thus not yet executed !)
    (*?) debugging symbols,
*/

#endif // DEBUGGER_HPP_INCLUDED
