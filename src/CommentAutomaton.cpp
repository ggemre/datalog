#include "CommentAutomaton.h"

#include <iostream>

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        Sm1(input);
    }
    else if (input[index] != '\n') {
        inputRead++;
        index++;
        Ss1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::Ss1(const std::string& input) {
    if (input[index] == '\n') {
        inputRead++;
        newLines++;
    }
    else if (input[index] != EOF) {
        inputRead++;
        index++;
        Ss1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::Sm1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        Sm2(input);
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        newLines++;
        Sm1(input);
    }
    else if (input[index] != EOF) {
        inputRead++;
        index++;
        Sm1(input);
    }
    else {
        isDefined = false;
    }
}

void CommentAutomaton::Sm2(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
    }
    else if (input[index] == '\n') {
        inputRead++;
        index++;
        newLines++;
        Sm1(input);
    }
    else if (input[index] != EOF) {
        inputRead++;
        index++;
        Sm1(input);
    }
    else {
        isDefined = false;
    }
}

Token* CommentAutomaton::CreateToken(std::string input, int lineNumber) { 
    std::string description = input.substr(0, index);
    if (isDefined) {
        return new Token(type, description, lineNumber); 
    }
    else {
        return new Token(TokenType::UNDEFINED, description, lineNumber);
    }
}