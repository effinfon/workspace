#ifndef STRINGPROCESSING_HPP_INCLUDED
#define STRINGPROCESSING_HPP_INCLUDED

// there are #MOVEOUT tags here

/// TD
/*  (*) analytic (*)
    find unique
    longest / shortest common
    intersections of n strings (start with 2 strings and find other interesting / useful properties)
    compare strings (?)
    superstrings: shortest, sum of sub-strings, eliminate doubling interfaces, try to find "inside merges"
    DNA sequencing
    generate symmetries of strings
    permute string (randomly or parametrically)
    parse CLI arguments, possibly of multiple formats <e.g.> -vsft vs -v -s -f -t vs --verbose --swift --force --temporal

*/
/*  (*) string similarity / approximations / document distance (*)

*/





#include <string>
#include <vector>

#define counter_type uint32_t






class Parser {}; // an abstraction for parsing strings, as a state-machine ...





// helper, (letter / character) classification funcions
bool isSpace(char c) {
    if(c == ' ' || c == '\t' || c == '\n') return true;
    return false;
}

bool isAlphaUpper(char c) {
    if(c >= 'A' && c <= 'Z') return true;
    return false;
}

bool isAlphaLower(char c) {
    if(c >= 'a' && c <= 'z') return true;
    return false;
}
bool isAlpha(char c) {
    if(isAlphaUpper(c) || isAlphaLower(c)) return true;
    return false;
}

bool isNumeric(char c) {
    if(c >= '0' && c <= '9') return true;
    return false;
}

bool isAlphaNumeric(char c) {
    if(isAlpha(c) || isNumeric(c)) return true;
    return false;
}

bool isIdentifierStart(char c) {
    if(isAlpha(c) || c == '_') return true;
    return false;
}

bool isIdentifierInside(char c) {
    if(isAlphaNumeric(c) || c == '_') return true;
    return false;
}

bool isIdentifier(std::string string) {
    // expects no space
    if(isIdentifierStart(string[0])) {
        for(counter_type idx {1}; idx < string.length(); idx++) {
            if(!isIdentifierInside(string[idx])) return false;
            else if (idx == string.length() - 1) return true;
        }
    } // else   // for some reason the compiler doesn't figure this out as being "covered" and warns about no return possibility
    return false;
}

// #MOVEOUT
bool existsIn(std::string element, std::vector<std::string> container) {
    for(std::string auto_element : container) {
        if(element == auto_element) return true;
    }

    return false;
}

std::vector<std::string> find_unique(std::string string) {
    std::vector<std::string> result {};

    counter_type idx = 0;
    std::string current {};

    bool inWord{false};

    while(idx < string.length()) {
        if(!inWord) {
            if(isSpace(string[idx])) idx++;
            else if(isIdentifierStart(string[idx])) { inWord = true; current += string[idx++]; }
        }
        else if(inWord) {
            if(isIdentifierInside(string[idx])) { current += string[idx++]; }
            else { if(!existsIn(current, result) && current != "") result.push_back(current);
                   current.erase(); idx++;
            }
            // there needs to be some handle for punctuation and eventually possible "punctuation words / sequences"
            // because as they are, they produce empty strings (fixed, short-term)
        }
    }
    return result;
}

bool isPangramAlphaInsensitive(std::string string) {
    int alpha_count[26] {};
    // ensure they are all upper case by forcing the "case bit" to 0,
    // afterwards, while iterating, count in the alpha-index

    for(char alpha : string) {
        alpha &= 0b11011111;
        alpha_count[alpha - 'A']++;
    }

    for(int idx = 0; idx < 26; idx++) {
        if(alpha_count[idx] == 0) return false;
    }

    return true;
}

#endif // STRINGPROCESSING_HPP_INCLUDED
