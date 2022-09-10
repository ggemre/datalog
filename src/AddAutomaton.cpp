#include "AddAutomaton.h"

void AddAutomaton::S0(const std::string& input) {
    if (input[index] == '+') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

Token* AddAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, 1);
    return new Token(type, description, lineNumber); 
}