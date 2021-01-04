#ifndef FILES_HPP_INCLUDED
#define FILES_HPP_INCLUDED

#include <string>
#include <filesystem>
#include <fstream>
#include "CollectionTypes.hpp"

namespace fs = std::filesystem;

/// TD
/*
    get current dircetory's path
    get list of all files in directory; or specify a path, see if it exists, see if it is a file or folder, and if it is a folder then get its list of contents
    have an iterator through a all sub-folders in a folder, which also prints each folder's contentx, starting with the "origin / root folder"
    have a file searcher
*/


namespace utilitaries {

////    FILE* file = popen("wget -r -np -A .txt http://www.google.com","r");
//    fs::directory_entry dir {fs::current_path()};
//    std::cout << dir << "\n";
////    std::cout << dir.

struct ls_data {
    std::vector<std::string> file_name {};
    std::vector<std::string> file_pathname {};
    std::vector<std::string> file_size {};
    std::vector<std::string> timestamp_last_modified {};
    std::vector<std::string> timestamp_created {};
    std::vector<std::string> owner {};
    std::vector<std::string> access_rights {};

    uint64_t count_results {0};

    void AddEntry(std::string file_name = std::string {});
};

    // (*?) maybe instead return an enum, and use a single function that checks everything in detail;
        // or, leave these be, as a specialized variant of each question; the function before mentioned will
        // be the ~ integration of all the specialized functions, or rather the properties they compute, because
        // the code is unlikely to make indirections to these specialized functions, because... "integration"
bool IsRelativePath(char const * path) {}
bool IsAbsolutePath(char const * path) {}

    // input: relative or absolute address; by default: nothing (current directory)
std::string ls(char const * path = "") {
    // return file-names
    bool file_names {true}; // basically, if the same file-name occurs at different depths, it will be the same -> (?) duplicates merge or "persist independently / separately" ?

    // returns file_pathnames, relative or absolute
    bool file_pathnames {true};
//    bool
    bool relative {true};
    bool absolute {false};

    // kinds of search
    bool recursive_search {false};
    bool current_directory_search {true};

    // returns metadata: file-size,
    bool file_size {false};
    bool last_modified {false};
    bool created {false};

    // returns metadata about access, users / owner, (user) groups
    bool owner {false};
    bool access_rights {false};

    if(IsRelativePath(path)) {
        // current path, etc.
    } else if (IsAbsolutePath(path)) {

    } else {
        printf("Invalid address / path.\n");
    }
}

    // (*!?) to be returned using std::move semantics; how to do that (?), needs it be declared in both the receiver and the sender ? what about the return statement ?
std::string loadFile(char const * file_pathname) {
    // (*?) "flexibility cases": starting '/' or ''; starting '.'; ending '/';

    // check file exists; check file type (not a directory, special file, symlink, etc, but instead a "regular" file
    std::string currentpath = std::filesystem::current_path();
    fs::exists(currentpath);

    // (*?) since the <filesystem> itself likely also deals with this internally, I am not sure if this is even necessary
//    if(IsRelative(file_pathname)) {}  //
//    else if (IsAbsolute(file_pathname)) {}

    // (*?) read the file in binary mode, get everything from it

    // (*?) no buffers used; read the file size and directly reserve exactly the needed ammount of memory
        // (i) use filesystem to get the file's size
        // (ii) use seekg(end) and tellg(?) to get the file's size

};

    // (*?) any file is in essnce a byte stream; a string stores byte-sized characters;
        // yet, I'd also like to encode bitstreams in files (*!?)
void OptimizeFile(std::string& file) {
    // eliminate spaces before a line end / new line character ('\n')
    // replace any CRLF / LFCR (or any other such apple-OS or microsoft-OS historical characters / formattings) with simply '\n'
    //
}
};
#endif // FILES_HPP_INCLUDED
