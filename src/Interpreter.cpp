#include <map>
#include <vector>
#include <algorithm>
#include "Interpreter.h"
#include "Tuple.h"

#include <iostream>

Interpreter::Interpreter() {
    db = new Database();
}

Interpreter::~Interpreter() {
    delete db;
}

/**
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

Relation* Interpreter::JoinRelations(std::string name, Relation* relA, Relation* relB) {
    std::vector<std::string> attributesA = relA->GetAttributes();
    std::vector<std::string> attributesB = relB->GetAttributes();
    std::map<int, int> matchingCols;

    // find all matching columns
    for (int i = 0; i < (int)attributesA.size(); i++) {
        for (int j = 0; j < (int)attributesB.size(); j++) {
            if (attributesA.at(i) == attributesB.at(j)) {
                matchingCols.insert(std::pair<int, int>(i, j));
            }
        }
    }

    // combine headers (into attributesA)
    for (std::string attributeB : attributesB) {
        attributesA.push_back(attributeB);
    }

    // combine tuples
    std::set<Tuple> joinedTuples;

    for (Tuple tA : relA->GetTuples()) {
        for (Tuple tB : relB->GetTuples()) {
            bool canJoin = true;

            for (std::pair<int, int> matches : matchingCols) {
                if (tA.At(matches.first) != tB.At(matches.second)) {
                  canJoin = false;
                  break;
                }
            }

            if (canJoin) {
                std::vector<std::string> nextTuple;

                for (std::string val : tA.GetValues()) {
                    nextTuple.push_back(val);
                }

                for (std::string val : tB.GetValues()) {
                    nextTuple.push_back(val);
                }

                joinedTuples.insert(Tuple(nextTuple));
            }
        }
    }

    Relation* newRelation = new Relation(name, attributesA);
    for (Tuple t : joinedTuples) {
        newRelation->AddTuple(t);
    }

    return newRelation;
}

bool Interpreter::EvaluateRule(Rule* r) {
    // 1. Evaluate the predicates on the right-hand side of the rule
    Predicate* head = r->GetHead();
    std::string name = head->GetId();
    std::vector<Predicate*> body = r->GetBody();
    std::vector<Relation*> resultRelations;
    bool updated = false;

    for (Predicate* p : body) {
        resultRelations.push_back(EvaluatePredicate(p));
    }

    // 2. Join the relations that result
    int relNum = resultRelations.size();
    Relation* joinedRelation = resultRelations.at(0);

    for (int i = 0; i < relNum - 1; i++) {
        joinedRelation = JoinRelations(name, resultRelations.at(i), resultRelations.at(i + 1));
        resultRelations.at(i + 1) = joinedRelation;
    }

    // 3. Project the columns that appear in the head predicate
    std::vector<std::string> joinedAttributes = joinedRelation->GetAttributes();
    std::vector<std::string> headAttributes;
    std::vector<int> projectedCols;

    for (Parameter* param : head->GetParameters()) headAttributes.push_back(param->ToString());
    int headAttrNum = headAttributes.size();
    int joinedAttrNum = joinedAttributes.size();

    for (int i = 0; i < headAttrNum; i++) {
        for (int j = 0; j < joinedAttrNum; j++) {
            if (headAttributes.at(i) == joinedAttributes.at(j)) {
                projectedCols.push_back(j);
                break;
            }
        }
    }

    joinedRelation = joinedRelation->Project(projectedCols);

    // 4. Rename the relation to make it union-compatible
    Relation* matchingScheme = db->entries[name];
    std::vector<std::string> schemeAttributes = matchingScheme->GetAttributes();
    joinedRelation = joinedRelation->Rename(schemeAttributes);

    // 5. Union with the relation in the database
    std::cout << r->ToString() << "." << std::endl;
    for (Tuple t : joinedRelation->GetTuples()) {
        bool dbChanged = db->entries[name]->AddTupleForRule(t);

        if (dbChanged) {
            updated = true;
            std::cout << "  " << t.ToString(joinedRelation->GetAttributes()) << std::endl;
        }
    }

    return updated;
}

void Interpreter::Interpret(DatalogProgram* datalog) {
    std::vector<Predicate*> schemes = datalog->GetSchemes();
    std::vector<Predicate*> facts = datalog->GetFacts();
    std::vector<Rule*> rules = datalog->GetRules();
    std::vector<Predicate*> queries = datalog->GetQueries();

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

    // 3. evaluate rules
    //      see EvaluateRule()
    std::cout << "Rule Evaluation" << std::endl;
    int ruleNum = rules.size();
    int passes = 0;
    bool looping = true;

    while (looping) {
        looping = false;
        for (int i = 0; i < ruleNum; i++) {
            bool changed = EvaluateRule(rules.at(i));
            if (changed) looping = true;
        }
        passes++;
    }

    std::cout << std::endl << "Schemes populated after " << passes << " passes through the Rules." << std::endl << std::endl;

    // 4. for each query 'q'
    //      see EvaluatePredicate()
    std::cout << "Query Evaluation" << std::endl;

    for (Predicate* q : queries) {
        Relation* resultRelation = EvaluatePredicate(q);
        std::cout << q->ToString() << "?";
        std::cout << resultRelation->ToString() << std::endl;
    }
}
