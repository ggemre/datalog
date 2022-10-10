#include <iostream>
#include "DatalogProgram.h"

DatalogProgram::~DatalogProgram() {
    for (Predicate* scheme : schemes) {
        delete scheme;
    }
    for (Predicate* fact : facts) {
        delete fact;
    }
    for (Predicate* query : queries) {
        delete query;
    }
    for (Rule* rule : rules) {
        delete rule;
    }
}

void DatalogProgram::AddScheme(Predicate* scheme) {
    schemes.push_back(scheme);
}

void DatalogProgram::AddFact(Predicate* fact) {
    facts.push_back(fact);
}

void DatalogProgram::AddQuery(Predicate* query) {
    queries.push_back(query);
}

void DatalogProgram::AddRule(Rule* rule) {
    rules.push_back(rule);
}

std::vector<Predicate*> DatalogProgram::GetSchemes() {
    return schemes;
}

std::vector<Predicate*> DatalogProgram::GetFacts() {
    return facts;
}

std::vector<Predicate*> DatalogProgram::GetQueries() {
    return queries;
}

/**
 * returns the parsed datalog program as a string
 * 
 * @return the each datalog vector passed into string stream as a string
 * @note if the parser threw an error, returns the error message instead
 **/
std::string DatalogProgram::ToString() {
    // if an error message was set (by parser), return error message
    if (!errorMessage.empty()) {
        return errorMessage;
    }
    else {
        CreateDomain();
        std::stringstream os;

        os << "Success!" << std::endl;

        // output each scheme predicate
        os << "Schemes(" << schemes.size()  << "):" << std::endl;
        for (Predicate* scheme : schemes) {
            os << "  " << scheme->ToString() << std::endl;
        }

        // output each fact predicate
        os << "Facts(" << facts.size() << "):" << std::endl;
        for (Predicate* fact : facts) {
            os << "  " << fact->ToString() << "." << std::endl;
        }

        // output each datalog rule
        os << "Rules(" << rules.size() << "):" << std::endl;
        for (Rule* rule : rules) {
            os << "  " << rule->ToString() << "." << std::endl;
        }

        // output each query predicate
        os << "Queries(" << queries.size() << "):" << std::endl;
        for (Predicate* query : queries) {
            os << "  " << query->ToString() << "?" << std::endl;
        }

        // output the domain
        os << "Domain(" << domain.size() << "):" << std::endl;
        for (std::string domainItem : domain) {
            os << "  " << domainItem << std::endl;
        }

        return os.str();
    }
}

/**
 * builds the domain for the current program
 **/
void DatalogProgram::CreateDomain() {
    for (Predicate* fact : facts) {
        for (Parameter* param : fact->GetParameters()) {
            domain.insert(param->ToString());
        }
    }
}

void DatalogProgram::SetErrorMessage(std::string message) {
    errorMessage = message;
}