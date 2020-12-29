#ifndef VERSIONCONTROL_HPP_INCLUDED
#define VERSIONCONTROL_HPP_INCLUDED

#include <filesystem>
#include <string>
#include <vector>

/// TD
/*
    file-wise versioning, with a diff visualization tool
    somehow identify "relevant diffs"
    diffs might (!*) include a suite of analyses done, to test what worked and how
        // well (for example performance benchmarks, static analyses, coverage analyses, whatever metrics, etc.)
    integrated into the IDE, of course; the IDE should also integrate a database, a "general / system AI" and
        // multiple sub-AIs ("specialized AIs")

*/
/*
    (*?) a reason for why I find git to be complicated is its interface; again, the idea of (!?) "visualizing the abstraction",
        which is absent in the design of the program (not to mention that there are also multiple ways to do the same thing with
        commands that are "hand-coded";
            // if it were about "using a general, powerful, simple domain programming language, of the program",
        then it would be a different story, but there are things such as "git checkout" vs "git switch" and "git ...?..." which do very
        similar things with "minute differences" (*?) and I find that to be very bad
    using graphics to visualize the "state of the repository" and by also making it "interactive", might make it easier to learn; also,
        there being a (*?) duality between GUI interaction and a domain language / ~ "scripting language" might help (?) [one thing the GUI
        has problems with is automation, but it's likely easier to use; on the other hand, when automating you don't need graphics, so you'd
        rather turn them off and use a ~ "(graphics) silent mode"; but then the problem is in using the domain language of the program requires
        having some ammount of knowledge about the system's functioning / structure (which the idea here is to supplement by providing
        a duality between GUI interactivity and the domain language [for any activity in the GUI, there is a bijection in the programming language (*?)]
*/

struct State {
    void* binary;
    uint64_t bytes;
};

struct MultiwayCommitTree {
    State* origin;
    std::vector<State*> next;
    uint64_t states;

    void Init() {}
    void Commit() {}    // a commit message (?)
    void Remove() {}    // will affect what follows (?); or things could be "collapsed to the next valid configuration / ~ merged"
    void RemoveRecursively() {} // delete everything after it
    void Branch() {}    // (*?)

    bool SelectActiveState() {}
    void DiffCompression() {}   // (*?) initially there's an effective copy of the whole new state; at some point, a diff will be computed, using some
                                // language to encode "removals" and "additions", etc.; (*?) "modifications" (adjacency of removal / deletion and addition / insertion)
                                // might be considered only later; but even so, it would be only in the basis of removals and insertions / deletions and additions

};

struct Repository {
    // list of files and their metadata, with hash and CRC of the entry itself (?)
    // ...
    // (*?) can contain multiple
    std::vector<std::pair<std::string /* name */, MultiwayCommitTree /* data */>> association;

    void Init() {}
    void CreateAssociation /* or CreateTree */ () {}
    void RemoveAssociation /* or RemoveTree */ () {}
};



#endif // VERSIONCONTROL_HPP_INCLUDED
