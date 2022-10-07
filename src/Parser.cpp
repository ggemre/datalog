#include <iostream>
#include "Parser.h"
#include "Token.h"
#include "DatalogProgram.h"

Parser::Parser(std::vector<Token*> lexerTokens) {
    tokens.swap(lexerTokens);
}

/**
 * does nothing if the current token is of the given type
 * if the current token is not of the type the token is thrown
 * 
 * @param type the token type to compare against
 **/
void Parser::ValidateToken(TokenType type) {
    if (tokens[index]->GetType() != type) {
        throw tokens[index];
    }
    else {
        index++;
    }
}

/**
 * entry function for parser, builds a datalog object from the tokens vector
 * recursively parses the tokens using the datalog grammar productions
 * 
 * @return the datalog program built by the parse functions
 **/
DatalogProgram* Parser::ParseDatalogProgram() {
    try {
        ValidateToken(TokenType::SCHEMES);
        ValidateToken(TokenType::COLON);

        ParseScheme();
        ParseSchemeList();

        ValidateToken(TokenType::FACTS);
        ValidateToken(TokenType::COLON);

        ParseFactList();

        ValidateToken(TokenType::RULES);
        ValidateToken(TokenType::COLON);

        ParseRuleList();

        ValidateToken(TokenType::QUERIES);
        ValidateToken(TokenType::COLON);

        ParseQuery();
        ParseQueryList();

        ValidateToken(TokenType::EOF_TOKEN);
    }
    // if an error is thrown, set the datalog error message
    catch (Token *offender) {
        std::stringstream os;

        os << "Failure!" << std::endl;
        os << "  " << offender->ToString() << std::endl;

        datalogProgram->SetErrorMessage(os.str());
    }
    return datalogProgram;
}

/**
 * part of the datalog grammar
 * parses schemeList nonterminals
 **/
void Parser::ParseSchemeList() {
    if (tokens[index]->GetType() == TokenType::ID) {
        ParseScheme();
        ParseSchemeList();
    }
}

/**
 * part of the datalog grammar
 * parses factList nonterminals
 **/
void Parser::ParseFactList() {
    if (tokens[index]->GetType() == TokenType::ID) {
        ParseFact();
        ParseFactList();
    }
}

/**
 * part of the datalog grammar
 * parses ruleList nonterminals
 **/
void Parser::ParseRuleList() {
    if (tokens[index]->GetType() == TokenType::ID) {
        ParseRule();
        ParseRuleList();
    }
}

/**
 * part of the datalog grammar
 * parses queryList nonterminals
 **/
void Parser::ParseQueryList() {
    if (tokens[index]->GetType() == TokenType::ID) {
        ParseQuery();
        ParseQueryList();
    }
}

/**
 * part of the datalog grammar
 * parses scheme nonterminals
 * 
 * @note adds a scheme to datalog program
 **/
void Parser::ParseScheme() {
    currentId = tokens[index]->GetDescription();
    ValidateToken(TokenType::ID);

    ValidateToken(TokenType::LEFT_PAREN);

    currentParams.push_back(new Parameter(tokens[index]->GetDescription()));
    ValidateToken(TokenType::ID);

    ParseIdList();

    ValidateToken(TokenType::RIGHT_PAREN);

    datalogProgram->AddScheme(new Predicate(currentId, currentParams));
    currentParams.clear();
}

/**
 * part of the datalog grammar
 * parses fact nonterminals
 * 
 * @note adds a fact to datalog program
 **/
void Parser::ParseFact() {
    currentId = tokens[index]->GetDescription();
    ValidateToken(TokenType::ID);

    ValidateToken(TokenType::LEFT_PAREN);

    currentParams.push_back(new Parameter(tokens[index]->GetDescription()));
    ValidateToken(TokenType::STRING);

    ParseStringList();

    ValidateToken(TokenType::RIGHT_PAREN);
    ValidateToken(TokenType::PERIOD);

    datalogProgram->AddFact(new Predicate(currentId, currentParams));
    currentParams.clear();
}

/**
 * part of the datalog grammar
 * parses rule nonterminals
 * 
 * @note adds a rule to datalog program
 **/
void Parser::ParseRule() {
    ParseHeadPredicate();

    ValidateToken(TokenType::COLON_DASH);

    ParsePredicate();
    ParsePredicateList();

    ValidateToken(TokenType::PERIOD);

    datalogProgram->AddRule(new Rule(currentHead, currentPreds));
    currentPreds.clear();
}

/**
 * part of the datalog grammar
 * parses query nonterminals
 * 
 * @note adds a query to datalog program
 **/
void Parser::ParseQuery() {
    currentParams.clear();
    ParsePredicate();

    ValidateToken(TokenType::Q_MARK);

    datalogProgram->AddQuery(new Predicate(currentId, currentParams));
    currentParams.clear();
}

/**
 * part of the datalog grammar
 * parses headPredicate nonterminals
 * 
 * sets the current headPredicate for current rule head
 **/
void Parser::ParseHeadPredicate() {
    currentId = tokens[index]->GetDescription();
    currentParams.clear();
    ValidateToken(TokenType::ID);

    ValidateToken(TokenType::LEFT_PAREN);

    currentParams.push_back(new Parameter(tokens[index]->GetDescription()));
    ValidateToken(TokenType::ID);

    ParseIdList();

    ValidateToken(TokenType::RIGHT_PAREN);

    currentHead = new Predicate(currentId, currentParams);
    currentParams.clear();
}

/**
 * part of the datalog grammar
 * parses predicate nonterminals
 * 
 * creates another predicate for current rule body
 **/
void Parser::ParsePredicate() {
    currentId = tokens[index]->GetDescription();
    ValidateToken(TokenType::ID);

    ValidateToken(TokenType::LEFT_PAREN);

    ParseParameter();
    ParseParameterList();

    ValidateToken(TokenType::RIGHT_PAREN);

    currentPreds.push_back(new Predicate(currentId, currentRuleParams));
    currentRuleParams.clear();
}

/**
 * part of the datalog grammar
 * parses predicateList nonterminals
 **/
void Parser::ParsePredicateList() {
    if (tokens[index]->GetType() == TokenType::COMMA) {
        ValidateToken(TokenType::COMMA);

        ParsePredicate();
        ParsePredicateList();
    }
}

/**
 * part of the datalog grammar
 * parses parameterList nonterminals
 **/
void Parser::ParseParameterList() {
    if (tokens[index]->GetType() == TokenType::COMMA) {
        ValidateToken(TokenType::COMMA);

        ParseParameter();
        ParseParameterList();
    }
}

/**
 * part of the datalog grammar
 * parses stringList nonterminals
 * 
 * creates another parameter for current predicate
 **/
void Parser::ParseStringList() {
    if (tokens[index]->GetType() == TokenType::COMMA) {
        ValidateToken(TokenType::COMMA);

        currentParams.push_back(new Parameter(tokens[index]->GetDescription()));
        ValidateToken(TokenType::STRING);

        ParseStringList();
    }
}

/**
 * part of the datalog grammar
 * parses idList nonterminals
 * 
 * creates another parameter for current predicate
 **/
void Parser::ParseIdList() {
    if (tokens[index]->GetType() == TokenType::COMMA) {
        ValidateToken(TokenType::COMMA);

        currentParams.push_back(new Parameter(tokens[index]->GetDescription()));
        ValidateToken(TokenType::ID);

        ParseIdList();
    }
}

/**
 * part of the datalog grammar
 * parses parameter nonterminals
 * 
 * creates another parameter for current predicate
 * @note rule bodyPredicate parameters are pushed seperately to clear IN BETWEEN predicates within rule
 **/
void Parser::ParseParameter() {
    if (tokens[index]->GetType() == TokenType::STRING) {
        currentParams.push_back(new Parameter(tokens[index]->GetDescription()));
        currentRuleParams.push_back(new Parameter(tokens[index]->GetDescription()));
        ValidateToken(TokenType::STRING);
    }
    else if (tokens[index]->GetType() == TokenType::ID) {
        currentParams.push_back(new Parameter(tokens[index]->GetDescription()));
        currentRuleParams.push_back(new Parameter(tokens[index]->GetDescription()));
        ValidateToken(TokenType::ID);
    }
}