#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Predicate.h"
#include "Relation.h"
#include "DatalogProgram.h"
#include "Database.h"

class Interpreter {
    private:
        Database* db;
        Relation* EvaluatePredicate(Predicate* p);
    public:
        ~Interpreter();
        void Interpret(DatalogProgram* datalog);
};

#endif // INTERPRETER_H