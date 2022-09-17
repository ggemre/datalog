#ifndef IDAUTOMATON_H
#define IDAUTOMATON_H

#include "Automaton.h"

class IdAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        if (isalpha(input[index]) || isdigit(input[index])) {
            inputRead++;
            index++;
            S1(input);
        }
        else if (input[index] == EOF) {
            Serr();
        }
    }

public:
    IdAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (isalpha(input[index])) {
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
        return new Token(type, description, lineNumber); 
    }
};

#endif // IDAUTOMATON_H