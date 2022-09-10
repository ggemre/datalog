#ifndef STRINGAUTOMATON_H
#define STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    bool doubleQuotes;

    void S1(const std::string& input);

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber);
};

#endif // STRINGAUTOMATON_H

