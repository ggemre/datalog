#include <map>
#include <vector>
#include <algorithm>
#include "Interpreter.h"
#include "Tuple.h"

#include <iostream>

Interpreter::~Interpreter() {
    delete db;
}

/**
 * 3. for each query 'q'
 * get the relation ‘r’ with the same name as the query ‘q’
 * select for each constant in the query ‘q’
 * select for each pair of matching variables in ‘q’
 * project using the positions of the variables in ‘q’
 * rename to match the names of variables in ‘q’
 * print the resulting relation
 */
Relation* Interpreter::EvaluatePredicate(Predicate* p) {
    std::string name = p->GetId();
    Relation* matchRelation = db->entries[name];
    Relation* intRelation = new Relation(matchRelation);

    std::vector<Parameter*> params = p->GetParameters();
    int paramNum = params.size();

    std::map<std::string, int> indicesOfVars;
    std::vector<std::string> parsedVars;

    for (int i = 0; i < paramNum; i++) {
        Parameter* param = params[i];

        // is constant, do select 1
        if (param->IsConstant()) {
            intRelation = intRelation->SelectVal(i, param->ToString());
        }
        else {
            // is not constant, is not new, do select 2
            if (std::count(parsedVars.begin(), parsedVars.end(), param->ToString())) {
                int firstIndex = indicesOfVars[param->ToString()];
                intRelation = intRelation->SelectSame(firstIndex, i);
            }
            // is not constant, is new, add to tracked vals
            else {
                indicesOfVars.insert(std::pair<std::string, int>(param->ToString(), i));
                parsedVars.push_back(param->ToString());
                intRelation->hasVars = true;
            }
        }
    }

    // project by tracked vals
    std::vector<int> indices;
    for (std::string var: parsedVars) {
        int nextIndex = indicesOfVars.at(var);
        indices.push_back(nextIndex);
    }
    intRelation = intRelation->Project(indices);
    
    // rename by tracked vals
    intRelation = intRelation->Rename(parsedVars);

    return intRelation;
}

void Interpreter::Interpret(DatalogProgram* datalog) {
    std::vector<Predicate*> schemes = datalog->GetSchemes();
    std::vector<Predicate*> facts = datalog->GetFacts();
    std::vector<Predicate*> queries = datalog->GetQueries();

    db = new Database();

    // 1. for each scheme 's'
    //      create a relation using name and parameter from 's'
    for (Predicate* s : schemes) {
        std::vector<std::string> attributes;
        for (Parameter* param : s->GetParameters()) attributes.push_back(param->ToString());

        std::string name = s->GetId();
        Relation* relation = new Relation(name, attributes);
        db->entries.insert(std::pair<std::string, Relation*>(name, relation));
    }

    // 2. for each fact 'f'
    //      make a tuple ‘t’ using the values from ‘f’
    //      add ‘t’ to relation with the same name as ‘f’
    for (Predicate* f : facts) {
        std::vector<std::string> values;
        for (Parameter* param : f->GetParameters()) values.push_back(param->ToString());

        std::string name = f->GetId();
        Tuple t(values);
        db->entries[name]->AddTuple(t);
    }

    for (Predicate* q : queries) {
        Relation* resultRelation = EvaluatePredicate(q);
        std::cout << q->ToString() << "?";
        std::cout << resultRelation->ToString() << std::endl;
    }
}