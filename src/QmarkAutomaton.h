#ifndef QMARKAUTOMATON_H
#define QMARKAUTOMATON_H

#include "Automaton.h"

class QmarkAutomaton : public Automaton
{
public:
    QmarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber);
};

#endif // QMARKAUTOMATON_H