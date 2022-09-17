#ifndef LEFTPARENAUTOMATON_H
#define LEFTPARENAUTOMATON_H

#include "Automaton.h"

class LeftParenAutomaton : public Automaton
{
public:
    LeftParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (input[index] == '(') {
            inputRead = 1;
        }
        else {
            Serr();
        }
    }

    Token* CreateToken(std::string input, int lineNumber) { 
        std::string description = input.substr(0, 1);
        return new Token(type, description, lineNumber); 
    }
};

#endif // LEFTPARENAUTOMATON_H