#ifndef RULE_H
#define RULE_H

#include <vector>
#include <string>
#include <sstream>
#include "Predicate.h"

class Rule
{
private:
    Predicate* head;
    std::vector<Predicate*> body;
public:
    Rule(Predicate* inpHead, std::vector<Predicate*> inpBody){
        head = inpHead;
        body = inpBody;
    }

    std::vector<Predicate*> GetBody() {
        return body;
    }

    Predicate* GetHead() {
        return head;
    }

    std::string ToString() {
        std::stringstream os;

        os << head->ToString() << " :- ";

        unsigned int bodyNum = body.size();
        for (unsigned int i = 0; i < bodyNum; i++) {
            os << body[i]->ToString();

            if (i < bodyNum - 1) {
                os << ",";
            }
        }

        return os.str();
    }
};

#endif // RULE_H