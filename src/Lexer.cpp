#include <string>
#include <cctype>
#include "Lexer.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QmarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for (Automaton* automaton : automata) {
        delete automaton;
    }

    for (Token* token : tokens) {
        delete token;
    }
}

/**
 * pushes each automaton onto automata vector
 **/
void Lexer::CreateAutomata() {
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QmarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new IdAutomaton());
}

/**
 * feeds through input and builds up token vector
 * 
 * this is the 1st block of the datalog pipeline
 * 
 * @param input file being read in as a string
 **/
void Lexer::Run(std::string& input) {
    int lineNumber = 1;

    // loops through each character of input
    while (input.length() > 0) {

        // count then remove new lines
        while (input.at(0) == '\n') {
            lineNumber++;
            input.erase(0, 1);
        }

        int maxRead = 0;
        Automaton *maxAutomaton = automata[0];

        // for each automaton, get inputRead
        for (Automaton *currentAutomaton : automata) {
            int inputRead = currentAutomaton->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = currentAutomaton;
            }
        }

        // if a token was identified, create and add to tokens
        if (maxRead > 0) {
            Token *newToken = maxAutomaton->CreateToken(input, lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            if (newToken->GetType() != TokenType::COMMENT) {
                tokens.push_back(newToken);
            }
        }
        // otherwise add token of type UNDEFINED
        else {
            maxRead = 1;
            if (input.length() > 0) {
                if (!isspace(input.at(0)) && input.at(0) != EOF) {
                    Token *newToken = new Token(TokenType::UNDEFINED, input.substr(0, 1), lineNumber);
                    tokens.push_back(newToken);
                }
            }
        }

        // erase all characters read
        for (int i = 0; i < maxRead; i++) {
            input.erase(0, 1);
        }
    }
    
    // append EOF token
    Token *newToken = new Token(TokenType::EOF_TOKEN, "", lineNumber);
    tokens.push_back(newToken);
}

std::vector<Token*> Lexer::GetTokens() {
    return tokens;
}