#ifndef COLONDASHAUTOMATON_H
#define COLONDASHAUTOMATON_H

#include "Automaton.h"

class ColonDashAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        if (input[index] == '-') {
            inputRead++;
        }
        else {
            Serr();
        }
    }

public:
    ColonDashAutomaton() : Automaton(TokenType::COLON_DASH) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (input[index] == ':') {
            inputRead++;
            index++;
            S1(input);
        }
        else {
            Serr();
        }
    }

    Token* CreateToken(std::string input, int lineNumber) { 
        std::string description = input.substr(0, 2);
        return new Token(type, description, lineNumber); 
    }
};

#endif // COLONDASHAUTOMATON_H

