#include "QueriesAutomaton.h"

void QueriesAutomaton::S0(const std::string& input) {
    if (input[index] == 'Q') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S1(const std::string& input) {
    if (input[index] == 'u') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S2(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S3(const std::string& input) {
    if (input[index] == 'r') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S4(const std::string& input) {
    if (input[index] == 'i') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S5(const std::string& input) {
    if (input[index] == 'e') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void QueriesAutomaton::S6(const std::string& input) {
    if (input[index] == 's') {
        inputRead++;
    }
    else {
        Serr();
    }
}

Token* QueriesAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, 7);
    return new Token(type, description, lineNumber); 
}