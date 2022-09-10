#include "CommaAutomaton.h"

void CommaAutomaton::S0(const std::string& input) {
    if (input[index] == ',') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

Token* CommaAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, 1);
    return new Token(type, description, lineNumber); 
}