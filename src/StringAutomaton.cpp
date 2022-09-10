#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '"') {
        inputRead++;
        index++;
        doubleQuotes = true;
        S1(input);
    }
    if (input[index] == '\'') {
        inputRead++;
        index++;
        doubleQuotes = false;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (doubleQuotes && input[index] == '"') {
        inputRead++;
        index++;
    }
    else if (!doubleQuotes && input[index] == '\'') {
        inputRead++;
        index++;
    }
    else if (input[index] != EOF) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

Token* StringAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, index);
    return new Token(type, description, lineNumber); 
}