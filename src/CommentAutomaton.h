#ifndef COMMENTAUTOMATON_H
#define COMMENTAUTOMATON_H

#include "Automaton.h"

class CommentAutomaton : public Automaton
{
private:
    bool doubleQuotes;

    void S1(const std::string& input);
    void Ss1(const std::string& input);
    void Sm1(const std::string& input);
    void Sm2(const std::string& input);

public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

    void S0(const std::string& input);
    Token* CreateToken(std::string input, int lineNumber);
};

#endif // COMMENTAUTOMATON_H

