#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
#include "DatalogProgram.h"

class Parser
{
private:
    DatalogProgram* datalogProgram = new DatalogProgram();

    int index = 0;
    std::vector<Token*> tokens;
    std::string currentId;
    Predicate* currentHead;
    std::vector<Predicate*> currentPreds;
    std::vector<Parameter*> currentParams;
    std::vector<Parameter*> currentRuleParams;

    void ValidateToken(TokenType type);

    void ParseSchemeList();
    void ParseFactList();
    void ParseRuleList();
    void ParseQueryList();
    void ParseScheme();
    void ParseFact();
    void ParseRule();
    void ParseQuery();
    void ParseHeadPredicate();
    void ParsePredicate();
    void ParsePredicateList();
    void ParseParameterList();
    void ParseStringList();
    void ParseIdList();
    void ParseParameter();

public:
    Parser(std::vector<Token*> lexerTokens);

    DatalogProgram* ParseDatalogProgram();
};

#endif // PARSER_H