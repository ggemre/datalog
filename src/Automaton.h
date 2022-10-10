#ifndef AUTOMATON_H
#define AUTOMATON_H
#include "Token.h"

class Automaton
{
protected:
    int inputRead = 0;
    int newLines = 0;
    int index = 0;
    TokenType type;

public:
    Automaton() : Automaton(TokenType::UNDEFINED) {}

    Automaton(TokenType type) { this->type = type; }

    virtual ~Automaton() {}

    /**  
     * start the automaton
     * read == 0 indicates the input was rejected
     * read  > 0 indicates the input was accepted
     * 
     * @return number of characters read by automaton
     **/
    int Start(const std::string& input) {
        newLines = 0;
        inputRead = 0;
        index = 0;
        S0(input);
        return inputRead;
    }

    // every subclass must define this method
    virtual void S0(const std::string& input) = 0;

    void Serr() {
        // indicate the input was rejected
        inputRead = 0;
    }

    virtual Token* CreateToken(std::string input, int lineNumber) { return new Token(type, input, lineNumber); }

    int NewLinesRead() const { return newLines; }
};

#endif // AUTOMATON_H