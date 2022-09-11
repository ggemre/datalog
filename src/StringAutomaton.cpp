#include <cctype>
#include "StringAutomaton.h"

#include <iostream>

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        newLines++;
        S1(input);
    }
    else if (input[index] != EOF) {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        isDefined = false;
    }
}

void StringAutomaton::S2(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else if (input[index] == EOF) {
        isDefined = false;
    }
}

Token* StringAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, index);
    
    if (isDefined) {
        return new Token(type, description, lineNumber); 
    }
    else {
        return new Token(TokenType::UNDEFINED, description, lineNumber);
    }
}