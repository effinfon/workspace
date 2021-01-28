#ifndef AIRENDER_HPP_INCLUDED
#define AIRENDER_HPP_INCLUDED

/// TD
/*
    a meaningful way in which simulation engines can be improved, as a technology, is to make them self-adaptive / autonomously learning,
         which implies a framework in which the renderer / simulation engine itself is self-programmable / trainable; this would basically end
         up being something such as: "code searcher", "model of general physics equations", "specialized AI fluid simulator", "specialized AI
         rigid / elastic body simulation", etc.
    the Unreal engine has great mechanisms, to make an engine from scratch and to reach their level is unfathomable; but, that is not the case if
        we're talking about automating the process of creating the engine; more so, it could / would be a better engine were it to be adaptive to
        use cases, adaptive to hardware, adaptive to changes in hardware and the operating system, adaptive to changes in resources, adaptive to
        changes in the network connectivity, adaptive to being in a computing cluster where nodes can go off or new ones can come on, adaptive to
        losing compute and having to redo it, ?? etc.
        // (*?) thus, the point is not to start making an engine from scratch, "by hand"; the point is to make it "by specification"; the way programming
            is to be done changes, the abstractions change, the versatility of the programming language changes; one can still program the old way, but
            programming the old way only ammounts to this: manually searching in a solution space that is otherwise defined by a specification; thus, should
            the AI searcher be incompetent, the human can help direct it by writting code itself; should the hardware used for the AI searcher be insufficient, the human programmer can
            help offload some of the work by writting code itself; should the AI searcher not have yet learned certain abstractions such as to be efficient on some complexity space, the
            human can ~ "teach" it or "guide" it (guide in the sense of giving it biased training data, which should / could make it converge faster in a given direction
            in its search) by writting code itself; the code being written is in the language being used for the search space, for example it could be C++ or even Java, or C, or Haskell,
            or Python, or Lisp, etc.
*/
/*
    animations: @~ 2:13 https://www.youtube.com/watch?v=DX92f8CrjrE
        this suggests that every character / body needs to have the same framework in the basis of which movement occurs, and thus the hero character does not get to
            have better animations than all the other characters; imagine that an intelligent AI (maybe even more intelligent than the hero player) is behind those
            other characters
    integration: @~ 3:00 https://www.youtube.com/watch?v=DX92f8CrjrE
        the game speed controls the audio rendition, as well as the "frame-physics" (it controls everything, basically; albeit, the frame rate is the same, as that
        is a separate control parameter)

*/

#endif // AIRENDER_HPP_INCLUDED
