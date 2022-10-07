#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <string>
#include "Tuple.h"
#include "Header.h"

class Relation {
    private:
        std::string name;
        Header header;
        std::set<Tuple> tuples;
    public:
};

#endif // RELATION_H