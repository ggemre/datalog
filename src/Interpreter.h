#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Predicate.h"
#include "Relation.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {
    private:
        Database* db;
        Graph* graph;
        Relation* EvaluatePredicate(Predicate* p);
        Relation* JoinRelations(std::string name, Relation* relA, Relation* relB);
        bool EvaluateRule(Rule* r, bool singleRule);
    public:
        Interpreter();
        ~Interpreter();
        void Interpret(DatalogProgram* datalog);
};

#endif // INTERPRETER_H