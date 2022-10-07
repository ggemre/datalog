#ifndef RELATION_H
#define RELATION_H

#include <set>
#include <string>
#include <vector>
#include "Header.h"
#include "Tuple.h"

class Relation {
    private:
        std::string name;
        Header header;
        std::set<Tuple> tuples;
    public:
        Relation SelectVal(int index, std::string val);
        Relation SelectSame(int firstIndex, int secondIndex);
        Relation Project(std::vector<int> indices);
        Relation Rename(std::vector<std::string> attributes);
};

#endif // RELATION_H