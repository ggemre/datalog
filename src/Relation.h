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
        bool hasVars = false;
        
        Relation(std::string inpName, std::vector<std::string> attributes);
        Relation(Relation* inpRelation);

        std::string GetName();
        std::vector<std::string> GetAttributes();
        std::set<Tuple> GetTuples();
        
        void SetValues(std::string inpName, std::vector<std::string> attributes);
        void Copy(std::string inpName, Header inpHeader);

        Relation* SelectVal(int index, std::string val);
        Relation* SelectSame(int firstIndex, int secondIndex);
        Relation* Project(std::vector<int> indices);
        Relation* Rename(std::vector<std::string> attributes);

        void AddTuple(Tuple tuple);
        std::string ToString();
        std::string ToStringAsRule();
};

#endif // RELATION_H