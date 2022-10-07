#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include <sstream>
#include "Parameter.h"

class Predicate
{
private:
    std::string id;
    std::vector<Parameter*> parameters;
public:
    Predicate(std::string inpId, std::vector<Parameter*> inpParams) {
        id = inpId;
        parameters = inpParams;
    }

    std::vector<Parameter*> GetParameters() {
        return parameters;
    }

    std::string ToString() {
        std::stringstream os;

        os << id << "(";

        unsigned int paramsNum = parameters.size();
        for (unsigned int i = 0; i < paramsNum; i++) {
            os << parameters[i]->ToString();

            if (i < paramsNum - 1) {
                os << ",";
            }
        }

        os << ")";

        return os.str();
    }
};

#endif // PREDICATE_H