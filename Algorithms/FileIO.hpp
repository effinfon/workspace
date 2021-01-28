#ifndef FILEIO_HPP_INCLUDED
#define FILEIO_HPP_INCLUDED

#include <string>
#include <filesystem>
#include <fstream>
#include "CollectionTypes.hpp"

#define BUFFER_SIZE 1024

namespace fs = std::filesystem;

/// TD
/*

*/


struct DoubleSequence {
    std::string filepathname {};
    std::string current_path {};
    DynamicArray<double> sequence {100};

    DoubleSequence(std::string filepathname) : filepathname(filepathname) {
        std::cout << "Current path is: " << fs::current_path() << "\n";
    }

    void loadFile() {
        current_path = fs::current_path();
        std::string total_path = current_path + '/' + filepathname;
        std::cout << total_path << "\n";
        std::string ram_file {};
        char buffer[BUFFER_SIZE] {};
        if(fs::exists(total_path)) {
            std::ifstream file = std::ifstream(total_path, std::ios_base::in);
            std::cout << "File found, loading...\n";
            while(file.getline(buffer, 1024)) { ram_file += buffer; for(uint32_t idx{0} ; idx < BUFFER_SIZE; idx++) buffer[idx] = '\0'; }
            std::cout << "The loaded file is:\n" << ram_file << "\n";
            file.close();
        } else {
            fprintf(stderr, "File not found.\n");
        }

        parse_string_sequence_double(ram_file);
    }

    void parse_string_sequence_double(std::string& string) {
        std::string current {};
        uint32_t idx {0};

//    repeat:
        while(idx < string.size()) {
            while(string[idx] == '\n' || string[idx] == ' ' || string[idx] == '\t' || string[idx] == ',' || string[idx] == ';') {
                idx++;
            }

            while('0' <= string[idx] && string[idx] <= '9') {
                current += string[idx++];
            } while(string[idx] == '\n' || string[idx] == ' ' || string[idx] == '\t' || string[idx] == ',' || string[idx] == ';') {
                idx++;
            } if(string[idx] == '.') {
                current += string[idx++];
            } while(string[idx] == '\n' || string[idx] == ' ' || string[idx] == '\t' || string[idx] == ',' || string[idx] == ';') {
                idx++;
            } while('0' <= string[idx] && string[idx] <= '9') {
                current += string[idx++];
            }

            sequence += std::stod(current);
            current.erase();
        }
    }

    double operator [] (uint32_t index) {
        return sequence[index];
    }
};
#endif // FILEIO_HPP_INCLUDED
