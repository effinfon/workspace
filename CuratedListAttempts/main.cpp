#include <iostream>

#include "ls.hpp"


bool AreIdenticalStrings(char* a, char* b) {
    uint64_t idx {0};
    while(a[idx] != '\0' && b[idx] != '\0') {
        if(a[idx] != b[idx]) {
            return false;
        }
        idx++;
    }
        // at least one is '\0', but are they both ?
    if(a[idx] != b[idx]) {
        return false;   // one is '\0' and the other is not
    }
        // they are both '\0'
    return true;
}

std::string programs[] {"ls"};

enum programs {
    ls_ID = 0,
    NONE
};

uint8_t isProgram(char* argv) {
    for(uint8_t idx {ls_ID}; idx < NONE; idx++) {
        if(AreIdenticalStrings(argv, const_cast<char*>(programs[idx].c_str())))
            return idx;
    }
    return NONE;
}

void CallProgram(uint8_t programID) {
    switch(programID) {
        case ls_ID:
            ls();
            break;

        case NONE:
        default:
            break;
    }
}

int main(int argc, char** argv) {
    // argv[1] is the program's name, then the rest are arguments for it if [1] exists and is recognized
    uint8_t programID {};
    if(argc > 1) {
        programID = isProgram(argv[1]);
        CallProgram(programID);
    }
}
