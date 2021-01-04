#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED

#include <filesystem>
#include <string>

namespace fs = std::filesystem;
/// TD
/*
    get current dircetory's path
    get list of all files in directory; or specify a path, see if it exists, see if it is a file or folder, and if it is a folder then get its list of contents
    have an iterator through a all sub-folders in a folder, which also prints each folder's contentx, starting with the "origin / root folder"
    have a file searcher
*/



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

    // relative or absolute; by default: nothing
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


}

//void loadFile() {
//
//        current_path = std::filesystem::current_path();
//        std::string total_path = current_path + '/' + filepathname;
//        std::cout << total_path << "\n";
//        std::string ram_file {};
//        char buffer[BUFFER_SIZE] {};
//        if(fs::exists(total_path)) {
//            std::ifstream file = std::ifstream(total_path, std::ios_base::in);
//            std::cout << "File found, loading...\n";
//            while(file.getline(buffer, 1024)) { ram_file += buffer; for(uint32_t idx{0} ; idx < BUFFER_SIZE; idx++) buffer[idx] = '\0'; }
//            std::cout << "The loaded file is:\n" << ram_file << "\n";
//            file.close();
//        } else {
//            fprintf(stderr, "File not found.\n");
//        }
//
//        parse_string_sequence_double(ram_file);
//    }

#endif // FILESYSTEM_HPP_INCLUDED
