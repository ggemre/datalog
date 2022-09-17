#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    bool isDefined = true;
    
    void S1(const std::string& input) {
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

    void S2(const std::string& input) {
        if (input[index] == '\'') {
            inputRead++;
            index++;
            S1(input);
        }
        else if (input[index] == EOF) {
            isDefined = false;
        }
    }

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (input[index] == '\'') {
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

#endif // STRINGAUTOMATON_H