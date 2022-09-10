#include <ctype.h>
#include "IdAutomaton.h"

void IdAutomaton::S0(const std::string& input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void IdAutomaton::S1(const std::string& input) {
    if (isalpha(input[index]) || isdigit(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
    else if (input[index] == EOF) {
        Serr();
    }
}

Token* IdAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, index);
    return new Token(type, description, lineNumber); 
}