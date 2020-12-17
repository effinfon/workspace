#ifndef CLI_HPP_INCLUDED
#define CLI_HPP_INCLUDED

#include <string>
#include "CollectionTypes.hpp"  // DynamicArray<typename>
#include "StringProcessing.hpp"

/// TD
/*
    check file exists; if not, report but no "halting error" unless necessary / "global or integrative process"
        that necessitates all files to exist
    verify recognized and unrecognized CLI arguments; report but no error, unless ??
*/

// program [options] [flags] file1 {file_i ...}
// options: "a" "b" "c" "d"
// flags: "-a" "-b" "-c" "-d"
// file1, file2, etc. -> stored in ~ FILE[]
/*
struct CLIStateMachine {
    // options are swappable, so are flags; state can be reset

    char const * const * options = {"a", "b", "c", "d"};
    char const * const * flags = {"-a", "-b", "-c", "-d"};
    char const * const * extra_flags = {"--flag1", "--flag2", "--flag3", "--flag4"};

    uint8_t state_register [3] {0, 0, 0};

    void ResetState() {
        for(uint8_t idx {0}; idx < sizeof(state_register); idx++) {
            state_register[idx] = 0;
        }
    }

    void SetBit(uint8_t idx_category, uint8_t idx_bit, bool bit) {
        uint8_t bitmask = bit;
        while(idx_bit) bitmask *= 2;

            // I found it necessary to do both of these operations; but is it (?!)
        state_register[idx_category] &= bitmask;
        state_register[idx_category] |= bitmask;
    }

    void Parse(char* argv) {
        ResetState();

        for(uint8_t idx{0}; idx < sizeof(options) / sizeof(char*); idx++) {
            isIdentical(argv, options[idx]);
        }
        for(uint8_t idx{0}; idx < sizeof(flags) / sizeof(char*); idx++) {
            isIdentical(argv, flags[idx]);
        }
        for(uint8_t idx{0}; idx < sizeof(extra_flags) / sizeof(char*); idx++) {
            isIdentical(argv, extra_flags[idx]);
        }
    }
};

bool CLI_v1(int argc, char** argv) {
    printf("argc: %d, argv: ", argc); for(int idx {0}; idx < argc; idx++) printf("%s ", argv[idx]); printf("\n");
}
*/
#endif // CLI_HPP_INCLUDED
