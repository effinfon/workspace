#ifndef SIMULATEDEVOLUTION_HPP_INCLUDED
#define SIMULATEDEVOLUTION_HPP_INCLUDED

#include <vector>

/*
    (*?!) these simulations should / could be "dynamic in scale, and objective (and overall framework)"; even the searcher
        strategy can dynamically change (*?)[such as not to say that "it can change with time"; but what is essentially the
        difference between "change with time" and "change dynamically" (*?!)]
        // (*?) the point here is that evolution does not seem to occur as a single optimization problem, and when it's done, it's done;
            instead it seems to be some sort of non-halting program [although it might end up, at times, or at some point, in some
            sort of (quasi) steady-state] that (interestingly) sort of "keeps becoming a different program", somehow; it can keep
            optimizing something different (objective change), and it also use a different state-space (?""?), etc.
    (*?) "changing environment"
    (*?) "robustness" and the "state-space / domain of correct functionality" (this could further be extended by thinking of
            "what environments has the system encountered, or might encounter in the future" and try to include those in the problem
            space; it might also be feasible at times to have "multiple solutions")
        // thus, whatever function / program / problem space evolution is, it seems to be general enough to decide when to "split
            a problem-space and try to find multiple solutions for a "domain of correct functionality" (actually, this domains gets
            ~ "split" into multiple sub-domains, and the solutions are found for those); an interesting complication arises here though,
            because what if the searcher could operate on a ~ "transform of the problem space" (the problem space has now become a
            composition of deciding the partitioning of the original domain and then to find good solutions in those partitions), but
            what if it could "operate across multiple partitionings, at once, and evaluate solutions's fitness even in that way (?!);
            well, also note that essentially, for enzymes at least, the fundamental search-space is the codon space (it is interesting
            to note here that if evolving enzymes, it is not strictly necessary to operate at the nucleotide level, but at the codon level;
            and this appears as a sort of modularity to me. or at least abstractization, because it does away with the details of optimizing
            nucleotidic robustness and protect against possible SNPs and errors that can appear at that level; the codon space solution can
            itself also do the same thing at its level, to try to find solutions that are "surrounded by an error-correction space",
            possibly even at a slight performance cost)
    (*?!) "what if tomorrow you have to re-design your solution, because some (little) detail(s) has (/ have) changed ?"
        this leads to things such as "learning generalizations of the search-space, so one can quickly re-orient themselves
            to solutions that fit the new (changing) conditions" (?!); so, instead of focusing solely on the performance of
            the solution, evolution could be seen as a sort of 2-level (or multi-level even) optimizer [but the order of the levels is problematic
            in itself though], one of the levels being that new solutions to changing situations need to be found quickly, so the way
            in which solutions are obtained needs to have some "reusability" to them [now, whether the mechanism has reusability or the
            solutions have reusability is confusing, because I'd think that both are affected by learning (*?)]
        the point here is that generalizations can act as a ~ modularity, in the sense that they are ~ "classifications of the search-space",
            therefore a great deal of the re-search becomes pre-compute based (specifically, to find the most likely class in which the
            solution to the new problem might be)
            // (*?"") "you don't have to redesign everything if you want to change one specific thing" (this assumes that the "specific thing"
                is "little")
            // (*?"") "you want to be able to change one trait without ruining everything else"
            // (*?"") "the successor parts need not be (greatly) affected by changes in their successors (/ dependencies); or otherwise,
                that they be able to automatically adjust"
                    (*?!) now this is two-fold: the first idea uses interfaces to ~ "separate" modules, but the other is a sort of "template
                        programming", because the specification knows how to adapt to changes in dependencies (at least up to as much as the
                        "domain of adaptability" is defined) <e.g.> "I want long arms (but the reason doesn't matter; what matters is how
                        the software gets re-written), so if I change things in the arms' program, there need not be (!?) `problems` / `functional
                        changes` or (!?) the need for `manual intervention` in the fingeres (or whatever modules have the arms as dependencies)"
                    (*?!) so essentially, evolution has to solve a problem similar to software engineering (and other kinds of engineering), and that
                        is about the speed at which a codebase / software can adapt to changes (!?)
            the point is that "likely, something that is very performant also generalizes rather poorly" (*?)[but what would be
                a satisfactory argument for this ? maybe that "global solutions" are "sparse" ? but are they ? is this in any way a property of
                non-constant functions ? I doubt so, because there could be periodic functions which produce a global solution with some period,
                so it's not very general]; the essential point is to ask whether "is it the fact that the searcher tries to find the most performant
                solution the problem, or that it is not intelligent enough, when it comes to having to then, very soon, find another solution to a
                different problem, that sorts of `throws away the previously found solution, because there is little reusability in it` ? but what
                determines the reusability of a solution ?"; well, if it comes to what the searcher learns about the search-space, then intelligence
                is that property, and the objective shouldn't have to do with that; but, when it comes to reusability of previous solutions, the solution
                itself does seem to matter
            (*?) the current matter is thus focused in parallel on "determining how does searcher learning affect the problem"
                and "what quantifies as (partial) reusability of a previously found solution and how to make futurely-found solutions more reusable ?"
    @~ 26:30 https://www.youtube.com/watch?v=cdaynA0PyPU
        (*?) does modularity really speed up evolution ? or in other words, is it really modularity that speeds up evolution ?
        (*?"") "to find the minimal thing we need to add to simulated evolution such that modularity starts to emerge" (!?)
    @~ 31:29 https://www.youtube.com/watch?v=cdaynA0PyPU
        (*?) the left graph has a missing connection; one can identify the symmetry of the graph and complete it; but the point is that there can be
        symmetry in an integrated solution to begin with
        (*?) thinking of implementing this myself, I arrived at the discussion of whether a more modular circuit is easier to parallelize the evaluation
            of, than a circuit that has more interdependence and would multi-thread less efficiently [due to more synchronization being necessary, and
            deciding that when a new thread should fork to evaluate some (serial) dependencies whilst the other evaluates a part independent of those
            dependencies, and so on]
    @~ 32:27 https://www.youtube.com/watch?v=cdaynA0PyPU
        (*?) the audience observes that in the case of a binary search-space, it is feasible to search both for max fitness and for min fitness; actually,
            the points of interest are fitness = 0 and fitness = 1 (in a [0, 1] normalized fitness space); the reason for that being that fitness = 1 is
            the function itself, whereas the function = 0 is the NOT of the funtcion (albeit, it does add one more operation to the function); but it's nice
            to be able to again parallelize even the directions in which one can search
        (*?) what the observation seems to essentially be is a "set of derived points from the currently sampled point", by way of "typical functions"
            // so by further thinking about it, the statement is actually wrong; a fitness = 0 solution does not mean a fitness = 1 solution, even in binary space;
                instead, it is the property that links ~ "opposite (/ not'ed) functions" in binary spaces, and in this case it's the NOT function itself, which
                can provide a fitness = 1 given a fitness = 0; but then one adds an overhead to the loop, which would be worth the cost, if it's small relative
                to what else goes on in the loop / "per iteration frame"
        (*?) the audience's observation is a nice idea though, it signifies that one can apply some "typical functions which in certain cases can actually
            produce / derive good solutions from bad solutions"; but the point remains, the fitness = 0 case is not part of the solution space, but its NOT form
            is part of the solution space and the fitness = 0 is not a solution by induction, but just a point from which one can map onto a fitness = 1 point, by
            way of the function NOT
        (*?) besides all this discussion, the linearity of the fitness functions was relevant in easily noting the correlation of fitness = 0 to fitness = 1 by way
            "of a single mutation / function" [though note that the NOT function is not the basis gate used, but instead the NAND gate is, so it will have to emulate
            the NOT gate; (!?) but, if searcher knows this, as a sort of modularity or generalization (?!), then it's done effectively in O(c) (*?)]
            // so the point is that which function maps a poor fitness solution to a high fitness solution is more or less difficult to observe, depending on the
                fitness space (and this is assuming that there are such functions; but it's safe to assume they do, but instead the problem remains how well they
                generalize; this means that if a rather obscure function is used, it will really only be useful in very specific cases, with low probability of
                being encountered)
            // (*!?) then an idea would be to first explore properties of the fitness space, trying to find functions which (!?) generally map poor solutions to
                good solutions; this way, one could also maintain a population of poor solutions and a population of good solutions (and the transition inbetween ?),
                for a better probability of a thorough search (?!)
    @~ 34:18 https://www.youtube.com/watch?v=cdaynA0PyPU
        (*?) if it were me, I'd like to do this: you can go ahead and use a gene for each gate, but the number of gates will vary, so instead make that a varible; next,
            (actually the more relevant part of the idea), would be to take out the cost form the fitness space (actually, this is not strictly necessary, but the searcher
            needs to have two criteria of selection then: one will be fitness, as usual; but another one will be "correctness", because this way it can know which
            solutions it can actually use, and then of those to have an ordering); but that is just the first step, because when writting a genomic program, one
            should instead write a parametrized function that (!?) "compresses all the correct solutions that are `worth` / `feasible`"; for example, the compression
            function would output a circuit with fewer elements if it's low on resourecs, or one  with more elements if it can (it all depends on the control input
            it receives; it doesn't decide, it receives the decision ! if by design it is forcefully needed for the function to decide, it will just be composed
            with a decision function; but is there even a difference between the two cases ? they would have composed either way... maybe unless one instead imagines
            that the design forces the `integration` of the two functions, which would end up as another search problem)
            // I still want to emphasize this point though: any criterion can be applied to the set of correct solutions; if the initial optimization that the speaker
                discusses has a cost per element integrated in the fitness, this does not mean that if all correct solutions are found, that the only evaluable
                criterion will also be the number of elements; instead, it can be any property, because given the set of correct solutions, one just iterates each solution
                and computes its score / corresponding point in an arbitrary fitness spcae, by an arbitrary fitness function (well, the fitness functions does need to be
                "compatible" with the solutions' data structure; for example, if the fitness functions requires 25 parameters, but the solutions are a dts with only 2
                parameters, then they are likely not to be "compatible" with the function; therefore, only all property / fitness functions applicable to the solutions)
        (*?) still not done, there is one more feature to integrate, and that is "transitions"; this means that the compression function, when it receives a "control
            input" / decision to change the current solution to another one, it will have to have a defined strategy for how the transition occurs; it might be gradual,
            such as if the solution space allows for it (it might have a grey code of step-changes which actually forms a continuous path through the solution space
            it compresses); or it might simply be the case that step-changes will instead pass through "equivalent points" to the solution space (thus not necessarily
            through the solutions themselves); but there might also be cases when the topology of these spaces is such that gradual change can only occur up to some interval,
            or maybe not at all, or maybe discontinuously (say, 7% of the path is continuous in one solution's equivalence space, then there is a discontinuity and it needs
            to "duplicate - redundancy", "generate the changes in the reserve" and then swap the reserve that has changes with the "active variant"; then again maybe continue
            through some solution's equivalence space, until a discontinuity happens again, and again...); another strategy might be to effectively create a reserve that is
            "decoupled from the system" / "inactive" until it accumulates all the necessary changes, and to then swap the active variant for the reserve (well, this too has
            some details of its own: you might need to first connect the reserve, ensure that it is connected and it works, and only then disconnect the original variant; or
            maybe there is a handler module that manages the functionality in a job-based / task-based manner, sowhenever the functionality is "available" it will give it one
            of the tasks that have been queued up by the handler, wait for the result, queue the result for when it can be communicated to the caller, etc.; so, this is a
            bit of a discussion of its own)
*/

/*
    (NAND gate)-based circuitry evolution -> to implement a function / objective (?)
        // implement AND, XOR, OR, NOT, etc.
        // implement "if(0) then {1}" and "if(1) then {0}" and "if(0) then {0}" and "if(1) then {1}"
        // what does NAND with constants {0, 1} produce ? and if they are nested ?
        // what does NAND with a single state (basically with x on all "free inputs") produce ? what if it's nested ?
        //
*/

struct Circuit {
/*
    struct Input {

    };
    struct Parameter : public Input {

    };

    struct Gate {

    };

    struct NAND : public Gate { // (*?) I wonder if I should use polymorphism; (*?!) note though that "conceptual polymorphism and similarity"
                                // does not necessarily overlap well with programatic polymorphism
    };

    struct Node {   // (*?) this feels better than to create something outside, called CircuitNode; at least internally it has a shorter name ... (?!)
        enum gate_type {
            NOT,
            AND,
            OR,
            XOR,
            NAND,
        };
    };
*/

    struct Node {
        uint64_t id;

        Node() {}
        Node(uint64_t id) {}

        virtual void AddConnection(Node node);
    };

    struct Parameter : public Node {
        std::vector<Node> outputs;

        Parameter(uint64_t id) : Node(id) {}
        Parameter(uint64_t id, std::vector<Node> outputs) : Node(id) {}

        virtual void AddConnection(Node node) {
            outputs.push_back(node);
        }
    };

    std::vector<Node> circuit;

    void SetParameters(uint64_t howMany) {
            circuit.erase();
            while(howMany--) { circuit.push_back(Parameter(circuit.size() + 1)); }
    }

    void AddConnection(uint64_t idSource, uint64_t idTarget) {
        circuit[idSource].AddConnection(idTarget);
    }
};

#endif // SIMULATEDEVOLUTION_HPP_INCLUDED
