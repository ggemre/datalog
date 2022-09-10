#include "SchemesAutomaton.h"

void SchemesAutomaton::S0(const std::string& input) {
    if (input[index] == 'S') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S1(const std::string& input) {
    if (input[index] == 'c') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S2(const std::string& input) {
    if (input[index] == 'h') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S3(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S4(const std::string& input) {
    if (input[index] == 'm') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S5(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S6(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}

Token* SchemesAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, 7);
    return new Token(type, description, lineNumber); 
}