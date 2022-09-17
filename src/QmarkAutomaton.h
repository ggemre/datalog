#ifndef QMARKAUTOMATON_H
#define QMARKAUTOMATON_H

#include "Automaton.h"

class QmarkAutomaton : public Automaton
{
public:
    QmarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (input[index] == '?') {
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

#endif // QMARKAUTOMATON_H