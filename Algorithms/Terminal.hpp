#ifndef TERMINAL_HPP_INCLUDED
#define TERMINAL_HPP_INCLUDED

/// Manifest
/*
    a terminal needs to be an interface that provides easy access to the programmer to
        information,data visualization, code editing and code execution, introspecting
        the system in detail (or at different levels of detail), to compile vast information
        into a format learnable by the programmer, to write scripts, to make schedules, to
        take notes, to scrap information, to inspect memory, to inspect hardware, to inspect
        drivers, to inspect the execution of other programs, to inspect source code and
        machine code, to reverse-engineer machine code, to do mathematics, to make proofs,
        to automatize data mining, ... etc.
*/

/// TD
/*
    terminology: (?"terminal", "console", "(user)/(IO)/(interaction) interface", etc.?)
    terminology: (?"CFG (context-free grammars)"?) [it doesn't take into consideration the discussion of what IS "context",
        as in the "previously made statements in the... context (?)" (look at lambda calculus, it uses the concept of "context"
        which kind fo symbolizes the "axioms" to be used when interpreting an expression)]

    font ("textures"), (*!?) "canvas" <e.g.> draw plots, enter commands, take notes, input
        photos and videos, etc. ... much like a wolfram notebook
    must use parallelism at "all levels": multi-thread support, vector processor support,
        graphics processors, kernel processors, etc.
    clipboard (?), history: undo / redo, ...
    color fonts (with fragment shaders -> even gradient colored fonts can be used, even textures, etc.)
    color profile: background, bars, fonts, cursor icon, etc.; everything needs to be re-programmable using
        shaders; shaders can be used to generate the content (*?)
    tabs, multi-tab support
    mouse interactivity -> right click (drop-down menu), "element / item selection (left click) and properties (right click)",
        ...
    execute programs, modify programs
    integrating an event system with the GUI and the shaders + rendering system; maybe a "parallel event handler" as well (?)
    multiple-mouse support (*?)
    code / command editing -> multi-pane (/ -window) support
    multi-terminal IDE (?); specialized terminals (?)
    programmable background
    in-terminal file search, possibly with GUI
    autocomplete features, GUI / terminal settings interface for what's already being searched and for managing (add, remove, etc.)
    canvas: I want the "tabs" to possibly be "windowless" (or "marginless" and "barless", like a "clean viewport only") and for
        them to be movable; thus, one could adjust and arrange say even 6-7 instructions / commands / processes running concurrently
        in the same "window"
    for automation purposes, there is not just "one active window" or just "on active tab" globally, and for each "handler" there
        might additionally be multiple concurrent ~ "streams" (such as multiple mouse devices in one tab, multiple cursors each
        with their associated keyboard device, etc.); there might be multiple cursor types: keyboard cursor (the blinking vertical
        bar for example), mouse cursor, etc. [cursors are basically a visualization, which can be disabled (*!?), that correlate to
        the positioning of an associated stream's of information "positioning" in the terminal, if that "makes sense for the device" (*!?)]
    (*!?) background automatization, virtual windows, accessible framebuffer (including the memory management, which should have some sort of
        lcok_guard for the framebuffer when an outside "thing" wants access (authentication -> authorization first though); the terminal
        program itself won't be blocked by this, but instead reserve itself new framebuffers (double framebuffers for its own work) and whenever
        something lock_guard a framebuffer, it will reserve itself a new one until that one is unlocked and can be freed (multiple requests could
        be made / scheduled ! but, if it is just reads, simultaneous access occurs; at this point, I don't see what a write access could do though)
        // (!?) actually, there is: an AI could process the framebuffer and "adjust it" with, say extra text, or generate soe image on top of it,
            or the terminal's framebuffer might contain text for an OCR AI that directly integrates into the terminal's framebuffer, etc. (*?)
    click events, mouse cursor + motions + hovering + etc., keyboard cursor + left-right movements + backspaces and spaces + typing according
        to some "typer / writter pattern profile", etc.
    "syntax file(s)" -> (*?) CFG machines (usually these are used to "color the lexicon" of the language recognized in a text; what else could
        these CFG machines be used for (*?)
    "CFG (start) points" (these are to be sued for parallelizing the parsing of "context-free grammars" -> parsing syntax on the fly; the next step
        would be to do static analysis in real-time as well, and possibly even "compilation-optimization" / "translation" (*?); suggestions could also
        be made by an "assistant";
    text processing on the GPU / vector processor (*!?)
    "fuzzy text / file search" (*?)

    its resolution and other parameteres (~ UI scale, font size, etc.) can be set before starting the program); the reason for this is that during
        ConwayLife's development, the terminal couldn't fully display the whole string of states on a single row and that made things difficult; otherwise,
        re-render what constitutes a "line" dynamically, as the size of the terminal window adjusts (which basically implies keeping a commands buffer of
        what has been rendered, instead of a pre-rendered framebuffer)
    when developing code, it would be nice to have a mechanism for quickly modifying libraries / imported source code (by, say, include <...>, which seems
        to "lock" the files from being changed), while leaving the original intact but creating a copy which gets modified and doing the "include modifications"
        for the programmer, ~ "switching between modes" of "use real libraries" vs "use prototyping libraries" (?!)
    ...
*/
/*
    using interrupt tables to execute code "in the program" and still be able to "return
        // control" -> warning: "inside code" might crash the whole program
    offer a feature for jumping straight into source code for modifying a program that executes (*?) -> pairing a program together with its source code
        and having them co-evolve / dynamically adapt; (*?) the program could also just have access to its own source code and decide how to modify itself (!?)
        // the idea for this stems from looking at highly configurable software, such as say VIm, or even CodeBlocks maybe; yes, it would result in a more size
            for the program, because the "reasoning" (static analysis, coverage, logic analysis and optimization, profiling, assembly and machine optimization,
            algebra, etc.) are all done in an "optimal" / efficient general-abstract-language and that gets to be "carried over", but it's an advantage for the
            program to be able to adjust itself at run-time (well, actually in the end there'd have to be some integration with the system on the hardware, so that
            optimizations could be of a "larger scope"
    .
*/

    // (*?) how do pointers to "empty structs" work in C/C++ (?) [or in any other language at that ?]
struct Window {};
struct Event {};

struct Terminal {
    Window* windows;
    Event* events;

    Terminal() {
        // upper bar (*?) -> title (dynamic <e.g.> '*' for files with unsaved changes, maybe even "blinkers", etc.),
            // buttons (right: min, max, close; left: triangle button ?), ... etc. ?
            // with / without upper bar
        //tabs bar (*?) -> File, Edit + Search, View, Settings, Help (?)
        // (*) tools bar (*?) -> maybe this could depend on the kind fo specialized terminal ... (?)
        // body / ~ a more dynamic viewport
    }
};

#endif // TERMINAL_HPP_INCLUDED
