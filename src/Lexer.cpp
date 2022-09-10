#include <sstream>
#include <string>
#include "Lexer.h"
#include "CommaAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
    
}

void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    /*
    set lineNumber to 1
    // While there are more characters to tokenize
    loop while input.size() > 0 {
        set maxRead to 0
        set maxAutomaton to the first automaton in automata

        // TODO: you need to handle whitespace inbetween tokens

        // Here is the "Parallel" part of the algorithm
        //   Each automaton runs with the same input
        foreach automaton in automata {
            inputRead = automaton.Start(input)
            if (inputRead > maxRead) {
                set maxRead to inputRead
                set maxAutomaton to automaton
            }
        }
        // Here is the "Max" part of the algorithm
        if maxRead > 0 {
            set newToken to maxAutomaton.CreateToken(...)
                increment lineNumber by maxAutomaton.NewLinesRead()
                add newToken to collection of all tokens
        }
        // No automaton accepted input
        // Create single character undefined token
        else {
            set maxRead to 1
                set newToken to a  new undefined Token
                (with first character of input)
                add newToken to collection of all tokens
        }
        // Update `input` by removing characters read to create Token
        remove maxRead characters from input
    }
    add end of file token to all tokens
    */

    int lineNumber = 1;

    while (input.length() > 0) {
        int maxRead = 0;
        Automaton *maxAutomaton = automata[0];
        unsigned int automataLen = automata.size();

        for (unsigned int i = 0; i < automataLen; i++) {
            Automaton *currentAutomaton = automata[i];

            int inputRead = currentAutomaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = currentAutomaton;
            }
        }

        if (maxRead > 0) {
            Token *newToken = maxAutomaton->CreateToken(input, lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else {
            // FIXME: here
            maxRead = 1;
            //Token *newToken = maxAutomaton->CreateToken(input, lineNumber);
            //tokens.push_back(newToken);
        }

        for (int i = 0; i < maxRead; i++) {
            input.erase(0, 1);
        }
        
        if (input.at(0) == '\n') {
            lineNumber++;
            input.erase(0, 1);
        }
    }
    
    Token *newToken = new Token(TokenType::EOF_TOKEN, "", lineNumber);
    tokens.push_back(newToken);
}

std::string Lexer::GetTokens() {
    std::stringstream os;
    
    unsigned int tokenNum = tokens.size();
    for (unsigned int i = 0; i < tokenNum; i++) {
        os << tokens[i]->ToString() << "\n";
    }

    return os.str();
}