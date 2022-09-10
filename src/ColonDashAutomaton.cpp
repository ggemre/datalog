#include "ColonDashAutomaton.h"

void ColonDashAutomaton::S0(const std::string& input) {
    if (input[index] == ':') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void ColonDashAutomaton::S1(const std::string& input) {
    if (input[index] == '-') {
        inputRead++;
    }
    else {
        Serr();
    }
}

Token* ColonDashAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, 2);
    return new Token(type, description, lineNumber); 
}