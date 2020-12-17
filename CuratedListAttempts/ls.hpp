#ifndef LS_HPP_INCLUDED
#define LS_HPP_INCLUDED

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;


/// TD
/*
    sym-links, hard-links, other such
*/
/*
    formatting seems useless at this point; there are plenty of options and possibilities, so I encourage
        the perspectvie of an "aware programmer, to the level of the code and with the ability to re-purpose /
        re-program programs easily"; that should make for a comfortable system (?!!); thus, with the power of a
        general-purpose programming language at hand, instead of having to memorize all the intricate details of
        someone else's program, instead one can build-up their own experience of the program, sort of by
        discovery learning; it is this mechanism of learning whose performance should me maximized, not stupid shit
        like using other people's libraries and "because OOP and high-level thinking", because no good decisions
        can be taken without some low-level knowledge (?!!) [actually , it's likely possible in some complexity spaces,
        but those would have to be ~ "well-modularized" complexity spaces, where only or mostly knowledge at that
        level of complexity matters from the POV of objective optimizations (?!); very interesting discussion actually]

*/

struct TimeDate{};  // with a cast to std::string

// concerns: Unicode characters, non-printable characters (replace them with spaces / '?' / or what (?!)
// supposedly files ending with '~' are "backups", whereas those starting with '.' are "hidden"
// can be sorted by any of these columns, so the columns should also be chosen with this in mind
// the result of an entry (~ relational database) can be anything obtainable from the composition of these columns / attributes
//
struct FileMetadata {
    std::string absolutePath {};
    std::string filename {};    // likely, but uncertain when duplicate filenames exist: to separate filename from file type suffix (?)
    /* TimeDate last_modified */ std::string timedate_last_modified {};
    /* Enum FileType */ std::string file_type;  // executable file, non-executable file, folder, symbolic, bitmap, jpeg, mp4, etc.
    uint64_t size_in_bytes;
    std::string owner; std::string author;  // do these differ, or can they differ ? well, technically I could imagine how, but is it practically relevant ?
    /* BitStream ? */ std::string rights;

};

// default location: current folder; if specified, it will take the argument as the target folder,
    // but first will verify if it is a folder or a different kind of file
// argument: with / without hidden files
// argument: with metadata or just filename
// argument: with absolute addresses (redundant, but maybe there are applications) or relative addresses to target folder
// argument: with or without implied "." and ".." folders
// argument: possibility to sort the output by a particular column <e.g> --sort-by="..."
// argument: possibility to filter by a regex expression <e.g.> --filter-by-regex="..." (*?!)
// argument: help -> it should print available arguments, columns available for --sort-by="...", etc.
// argument: print only folders, or only files, or only a particular file type, or anything that fits a regex (*?!)
// argument: classify / sort output by file type extensions
// argument: sorting can become even more complicated, with multi-attribute sorting being explicitated (*?)
// argument: whether to "iterate recursively" / "go to some depth in the folder hierarchy" (but now those paths / filenames
    // would need to contain some addressing, and probably a new type for the metadata)
// argument: whether to "dereference" file links or not

// the return type mechanism is not very versatile; there are cases that, depending on the
    // input arguments, the return type would be more efficiently one of multiple possibilities,
    // for example "ls -l" outputs much metadata about files, whereas just "ls" simply outputs
    // the filenames of the contents; uisng void return types on the other hand doesn't take
    // advantage of the type system's verifier; as such, it is both a lack of syntactic mechanism
    // that leads to more code dupliaction, but on the other hand it's sometimes (as in this case,
    // since a sort of "input's semantics -dependent return type overloading" is needed) about
    // a ~ "impossibility" of implementing something (actually, it's very much possible, but it goes
    // from being ~ "hardware accelerated / language supported" to being ~ "software emulated" (!?)
// when designing the regex, consider that the pattern can be either "positive" or "negative" (meaning whether
    // string that match the pattern are "accepted" or "rejected")
//
void ls() {
    std::string current_directory = fs::current_path().u8string();
    std::cout << "Folder " << current_directory << " contains:\n";

    // how can this be multi-threaded (?!)
    // the multi-threaded design already gives signs that it needs to
        // emerge from the OS itself as well; without OS support, some
        // tasks simply cannot be parallelized
    std::vector<std::string> contents {};
    for (auto & entry : fs::directory_iterator(current_directory)) {
        contents.push_back(entry.path());
    }

    for(const auto entry : contents) {
        std::cout << entry << "\n";
    }
}

#endif // LS_HPP_INCLUDED
