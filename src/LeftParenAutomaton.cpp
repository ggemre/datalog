#include "LeftParenAutomaton.h"

void LeftParenAutomaton::S0(const std::string& input) {
    if (input[index] == '(') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

Token* LeftParenAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, 1);
    return new Token(type, description, lineNumber); 
}