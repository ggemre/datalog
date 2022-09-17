#ifndef RIGHTPARENAUTOMATON_H
#define RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton
{
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (input[index] == ')') {
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

#endif // RIGHTPARENAUTOMATON_H