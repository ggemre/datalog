#ifndef SCHEMESAUTOMATON_H
#define SCHEMESAUTOMATON_H

#include "Automaton.h"

class SchemesAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        if (input[index] == 'c') {
            inputRead++;
            index++;
            S2(input);
        }
        else {
            Serr();
        }
    }

    void S2(const std::string& input) {
        if (input[index] == 'h') {
            inputRead++;
            index++;
            S3(input);
        }
        else {
            Serr();
        }
    }

    void S3(const std::string& input) {
        if (input[index] == 'e') {
            inputRead++;
            index++;
            S4(input);
        }
        else {
            Serr();
        }
    }

    void S4(const std::string& input) {
        if (input[index] == 'm') {
            inputRead++;
            index++;
            S5(input);
        }
        else {
            Serr();
        }
    }

    void S5(const std::string& input) {
        if (input[index] == 'e') {
            inputRead++;
            index++;
            S6(input);
        }
        else {
            Serr();
        }
    }

    void S6(const std::string& input) {
        if (input[index] == 's') {
            inputRead++;
        }
        else {
            Serr();
        }
    }

public:
    SchemesAutomaton() : Automaton(TokenType::SCHEMES) {}  // Call the base constructor

    void S0(const std::string& input) {
        if (input[index] == 'S') {
            inputRead++;
            index++;
            S1(input);
        }
        else {
            Serr();
        }
    }
    
    Token* CreateToken(std::string input, int lineNumber) { 
        std::string description = input.substr(0, 7);
        return new Token(type, description, lineNumber); 
    }
};

#endif // SCHEMESAUTOMATON_H