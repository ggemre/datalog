#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H

#include <vector>
#include <string>
#include <set>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram
{
private:
    std::vector<Predicate*> schemes;
    std::vector<Predicate*> facts;
    std::vector<Predicate*> queries;
    std::vector<Rule*> rules;
    std::set<std::string> domain;

    std::string errorMessage;

    void CreateDomain();

public:
    ~DatalogProgram();

    void AddScheme(Predicate* scheme);
    void AddFact(Predicate* fact);
    void AddQuery(Predicate* query);
    void AddRule(Rule* rule);

    std::vector<Predicate*> GetSchemes();
    std::vector<Predicate*> GetFacts();
    std::vector<Predicate*> GetQueries();

    void SetErrorMessage(std::string message);

    std::string ToString();
};

#endif // DATALOGPROGRAM_H