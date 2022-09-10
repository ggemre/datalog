#ifndef IDAUTOMATON_H
#define ID_AUTOMATON_H

#include "Automaton.h"

class IdAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IdAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber);
};

#endif // IDAUTOMATON_H