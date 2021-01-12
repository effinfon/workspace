#ifndef IDE_HPP_INCLUDED
#define IDE_HPP_INCLUDED

#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <iostream>
namespace fs = std::filesystem;

#include "Parser.hpp"

/// TD
/*
    (*?) imagine visual studio's right-side ~ "column of code"; now imagine a "graph style, code-space viewer"; the point is to see whether
        a codebase visualization is feasible which is not so "linear"; the point would be to also arrange the codebase in a "non file based architecture" (*!?)
    "code hiding" -> as with comments (a modification of color, but also of transparency !), so color palletes and transparency, the possibility for ~ "transparency
        inversion" between source code and comments and vice-versa, ...
    dynamic "jump to code"; usable (especially) in the TODO lists, but it should be a "general feature" (usable "anywhere else" in the IDE, as well)
    there is an essential problem with "pointer syntax" vs "reference syntax" (which up until now I have not yet understood) vs "?usual / integral? syntax" [which is
        // "as if you're operating with the values in memory, and not with their addresses or their references" (whatever the difference between those two might be)];
        // thus: a digramatic representation that "digs through the type of a variable / a `memory instance`" (or its ~ "structural hierarchy"), and clarifies to the
            programmer, in a visual manner, what the structure / hierarchy (pointer wise, reference wise, value wise, etc.) is [including whether it's stack allocated,
            heap allocated, or ()]
    ~ "auto-adjuster of indentation", dynamically intervening (or a sort of "indentation style maintainer"); especially useful when modifying code, at the level of
        control structures <e.g.> @~ 15:00 "Default values, explicit uninitialization (part 1)" - Jonathan Blow
    a "delete whole line" and a "delete all to the right of the cursor, on this line" (same video reference as above; very useful)
    (*?) a macro processor and a template processor, being aware of strings in a functionally complete way, and being aware of types in a convenient way; I think the two
        are useful merged; also, the macro processor is likely the superset, whereas the template processor is a subset of it which abstracts a lot of complexity
    search for all the occurences of something (and optionally automatically put a breakpoint on those lines where it is found)
    line numbers need to be displayed; errors, warnings, questions, etc. which have knowledge of the file-line number-column number need to be able to jump in-code
        exactly at those places
    (*?) what about errors / warnings / questions which can be more "vague" and only deduce a general are in-code / scope where the phenomenon occurs (?)
    (*?) search in a file, search in a pre-made list of files, search in the whole codebase, search across multiple codebases
    (*!?) given the objective of system-wide integration, it is the case that at some point it will be required to "merge / integrate multiple codebases", thus
        similarly to how git produces conflict reports on mergers / joins (or whatever they call them), so will the codebase merger [except it's likely a problem
        of greater complexity: (i) possibly multiple languages that all have to be translated to "the language"; (ii) resolving the dependencies of each codebase;
        (iii) compatibility of the codebases as source code (they might work fine together / be compatible as compiled programs, but that does not imply that their
        source codes are compatible) (*!?); (iv) reverse-compiling / decompiling libraries (into "the language"); (v) etc. (*?)]
    move the cursor to the top / bottom of the current function, or of the current scope, etc.
    (*!!?) not everything that does a specific thing has to be a function (especially because then there's additional structural complexity in indirecting everything); so
        what I desire actually is for the IDE to provide a mechanism of effectively "collapsing selected code" and allowing me to explicitate a specification for that
        selection; that way, code can be written even in large functions which will be "re-describable abstractly" (by this ~ "collapse and replace" mechanism) and even
        be verified for correctness according to the specification {locally define a ~ "interface" and the domain for the interface, and then the outputs can either also be
        explicitated element by element (or "case by case), or if a ~ "compression" [or "feature", or "AI filter", or "(learnt) abstraction by ML", etc.] is known then
        a specification can be explicitated}
        // the point is that this could greatly increase the speed for debugging things, and the specification and checks (otherwise called the "tests") do not actually
            have to be deleted afterwards, and can probably even be reused (!?)
        // (*?) yet, another discussion has to be had about "code reusability"; since some sort of "in-scope interface" is being defined for the code, and an analysis is done about
            what "out of scope (dependencies)" it has, it can thus be verified where is it eligible for it to be reused, it can be given an identifier [of sorts, maybe in a
            different list (*?)], etc.
    typo checker (?) [I don't want ti to pester me about where the dash '-' is placed though, only about the words themselves being correct; what this means is exemplified by
        "take-down" - I only care that "take" and "down" be correct]

    ...
*/
/*  SEARCH MECHANISMS

    to be able to search in all:
        // open files
        // project files
        // recursively through all includes (!?) <e.g.> I tried finding where "rotl" was implemented or at least defined, but it was (maybe) burried somewhere in the includes
*/

namespace IDE {
std::string AddFileToCodeblocksProject(fs::path pathFilename) {
    std::string result {"\t\t<Unit filename=\""};
    result += pathFilename;
    result += "\" />\n";

    return result;
}

fs::path GetRelativePathDistance(fs::path currentDirectory, fs::path destinationDirectory) {
    // for Codeblocks
}

// (*?) could add file-filters here, such as *.hpp *.cpp *.h *.c etc.
std::vector<fs::path> GetFiles(bool recursively, fs::path path) {
    if(fs::is_directory(path)) {
        std::filesystem::directory_iterator it {path};

        std::vector<fs::path> files;
        for(auto& filename : it) {
            if(fs::is_regular_file(filename)) {

                files.push_back(filename);
                std::cout << "Added file " << filename << "\n";
            }

            else if(recursively && fs::is_directory(filename)) {
            std::cout << "Found directory " << filename << "\n";
            std::vector<fs::path> recursive_files = GetFiles(recursively, filename);
            files.insert(files.end(), recursive_files.begin(), recursive_files.end());
        }   }

        return files;
    }
}

    // (*?) "start character match" -> "matchedness, sequential iterator"
uint64_t FindString(std::string pattern, std::vector<std::string> lines) {
    printf("Looking for pattern %s\nThe input has %lu lines\n", pattern.c_str(), lines.size());
    uint64_t count_loops {0};

    for(uint64_t idx_line {0}; idx_line < lines.size(); idx_line++) {
//        printf("count: %lu, ", count_loops++);
        for(uint64_t idx_start_col {0}; lines[idx_line].size() >= pattern.size() &&
                                        idx_start_col < lines[idx_line].size() - (pattern.size() - 1); idx_start_col++) {
//            printf("count: %lu, ", count_loops++);

            // (*?) "if for()" control structure ?
            bool match {true};

            for(uint64_t idx_col {0}; idx_col < pattern.size(); idx_col++) {
//                printf("count: %lu, ", count_loops++);
                if(pattern[idx_col] != lines[idx_line][idx_start_col + idx_col]) { match = false; break; }
            }

            if(match) return idx_line;
        }
    }

    return uint64_t(-1);
}

    // preferably absolute addresses for now
    // (*?) at some point, an abstraction that "contextually differentiates between relative and absolute addresses" (the context is in the string !)
    // (*!?) I want to be able to modify directly in the file... or would that be bad for the hardware ? was it purposely done this way such as to avoid
        // the reduced transmission of IO to HDD ? what about "direct file editing" for "parts" of it (?!) [granularity: maybe a row ? a line ? a paragraph ?; I don't
        // think there is a "row" in the context of a file... a "row" exists when rendering text... (*?)]
void AddFileToProject(std::string project_path_filename, std::vector<fs::path> files_to_add) {
    for(uint64_t idx {0}; idx < files_to_add.size(); idx++) {
        printf("File to be added: %s\n", files_to_add[idx].c_str());
    }

    // read it
    ifstream project_file_read {project_path_filename};
    if(!project_file_read.is_open()) { printf("File %s not found\n", project_path_filename.c_str()); return; }

    std::vector<std::string> read_whole_file {};
    std::string line {};
    while(std::getline(project_file_read, line)) {
//        std::string temp = *(new std::string(line));  // (*?) what does this actually do ?
        std::string temp = *(new std::string(line));
        temp += "\n";
        read_whole_file.push_back(temp);
        printf("Reading: %s", temp.c_str());
    }
    project_file_read.close();

    static std::string match {"<Extensions />"};
    uint64_t line_index = FindString(match, read_whole_file);
    printf("Found a string match at line number %lu\n", line_index);

    std::vector<std::string> reserve {};
    for(uint64_t idx {line_index}; idx < read_whole_file.size(); idx++) {
        printf("Reserving: %s\n", read_whole_file[idx].c_str());
        reserve.push_back(*(new std::string(read_whole_file[idx])));
    }

    // (*?) I suppose that ways in which an iterator can be different from a raw pointer, especially for std::vector<T> which is a reallocating array,
        // is that it has to abstract the reallocation of the array... right ? I hope so...
//    uint64_t idx {0};
//    for(; idx < files_to_add.size() && it2 != read_whole_file.end(); idx++, it2++) {
//        *it2 = AddFileToCodeblocksProject(files_to_add[idx]);
//

    if(line_index != uint64_t(-1) && line_index > 0) {
        read_whole_file.resize(line_index - 1);
    }

    for(uint64_t idx {0}; idx < files_to_add.size(); idx++) {
        uint64_t index = FindString(files_to_add[idx], read_whole_file);
        if(index == uint64_t(-1)) {
            std::string allocated = *(new std::string(AddFileToCodeblocksProject(files_to_add[idx])));
            printf("At index %lu, adding file: %s\n", line_index + idx, allocated.c_str());
            read_whole_file.push_back(allocated);
        }
    }
    for(auto& line : reserve) {
        printf("At index %lu, adding file: %s\n", read_whole_file.size(), line.c_str());
        read_whole_file.push_back(*(new std::string(line)));
//        read_whole_file.push_back(line);
    }
    // output it
    ofstream project_file_write {project_path_filename};
        // (*?) beware: this is a case of information loss (!)
    if(!project_file_write.is_open()) { printf("Cannot write to file %s.\n", project_path_filename.c_str()); return; }
    for(auto& line : read_whole_file) {
        project_file_write << line;
    }
    project_file_write.close();
}
};
#endif // IDE_HPP_INCLUDED
