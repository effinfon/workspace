#ifndef SYSTEMMEMORYPROFILER_HPP_INCLUDED
#define SYSTEMMEMORYPROFILER_HPP_INCLUDED

/// TD
/*
    (*?) terminology: "global memory integrator", "system-wide memory profile(r)", etc.
    (*?) this is ment to be an (AI) model that learns the circumstances of all the programs
        running on the system, and learning how to make decisions that optimize (?) whatever
        the training functions decree, those decisions are sent to programs (*?) [or some other
        mechanism might be used, but it must not make use of any supplementary memory] and
        that will result in the adaptation of the process's (?"memory profile (logic)"?) (*?); the
        point is to not have to manually code and make all the decisions regarding which program
        is handled how, but to instead only have to define / specify the objectives (with the added
        advantage that it automates the integration of new programs, which would indeed result in the
        growth in size of the model)
    (*?) the continuation of the above idea would be also automate (at least) the discovery of possible
        memory profiles for a program [it would be even better if given some ~ naive / stock version of
        a program, namely the source code, that the modification of the code such as to include
        memory profiles which are found to be "globally relevant (phases)" were automated, including the
        compilation and loading in memory, and eventually modifying the executable on the SSD, all without
        interrupting the execution of the program; you want too much for how uncapable you are... me]
*/

#endif // SYSTEMMEMORYPROFILER_HPP_INCLUDED
