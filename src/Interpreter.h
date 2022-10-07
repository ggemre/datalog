#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Predicate.h"
#include "Relation.h"

class Interpreter {
    private:
    public:
        Relation* EvaluatePredicate(const Predicate& p);
};

#endif // INTERPRETER_H