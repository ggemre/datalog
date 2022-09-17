#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton
{
private:
    bool isDefined = true;

    void S1(const std::string& input) {
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

    void Ss1(const std::string& input) {
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

    void Sm1(const std::string& input) {
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

    void Sm2(const std::string& input) {
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

public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (input[index] == '#') {
            inputRead++;
            index++;
            S1(input);
        }
        else {
            Serr();
        }
    }

    Token* CreateToken(std::string input, int lineNumber) { 
        std::string description = input.substr(0, index);
        if (isDefined) {
            return new Token(type, description, lineNumber); 
        }
        else {
            return new Token(TokenType::UNDEFINED, description, lineNumber);
        }
    }
};

#endif // COMMENTAUTOMATON_H