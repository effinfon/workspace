#ifndef KNOWLEDGEBASE_HPP_INCLUDED
#define KNOWLEDGEBASE_HPP_INCLUDED

#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <thread>

/*

*/

/// Todo: implement opening a new directory as a call on another thread
/// Todo: further improve the multi-threaded model; it should instead function with a fixed number of threads (4 or 8) and
    /// they should all share the directories that have to be searched, preferably also by querying each directory for the
    /// number of files inside it and then distributing these among the threads
/// Todo: multi-threaded design for interacting with the out's push_back() [how to pass the mutex around ? make it independent
    /// of the number of "instances" of this function; an instance of a function counts as a call with a root directory, not the
    /// function calls that derive from there]
std::vector<std::filesystem::path>* GetAllFiles(std::filesystem::path search_dir, std::vector<std::filesystem::path>* out = nullptr) {
    //std::cout << "Searching at path " << search_dir << "\n";

    if(std::filesystem::is_directory(search_dir)) {
        if(out == nullptr) { out = new std::vector<std::filesystem::path>(); }
        std::vector<std::thread> locally_managed_threads {};

        for (const auto & entry : std::filesystem::directory_iterator(search_dir)) {
            if(std::filesystem::is_regular_file(entry) && !std::filesystem::is_symlink(entry)) {
                out->push_back(entry.path());
                //std::cout << "Found file " << entry.path() << "\n";
            } else if (std::filesystem::is_directory(entry) && !std::filesystem::is_symlink(entry)) {
                GetAllFiles(entry.path(), out);
        //        locally_managed_threads.push_back(std::thread(GetAllFiles, entry, out));
            }
        }

        for(int i {0}; i < locally_managed_threads.size(); i++) {
            locally_managed_threads[i].join();
            std::cout << "joined local thread #" << i << "\n";
        }
    }
}

std::vector<std::filesystem::path>* Filter(std::vector<std::filesystem::path>* in = nullptr) {
    if(!in) {
        /*
            files without an extension are likely text files
            .pdf, .epub, .djvu, .chm, ... - but in principle everywthing has to be converted to .pdf, and then the AI will be trained on .pdf files
        */
        /*
            then it's images that are likely to be screenshots, or somehow relevant to me
        */
        /*  ESSENTIALLY

            positive (and negative) filtering based on filename analysis (~ regex pattern matches)
            content analysis, word frequency, ...
        */

        std::cout << in->size();

        for(auto const & entry : *in) {
            std::cout << entry << "\n";
        }
    }
}

#endif // KNOWLEDGEBASE_HPP_INCLUDED
