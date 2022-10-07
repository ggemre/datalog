#include <sstream>
#include <algorithm>
#include "Relation.h"

Relation::Relation(std::string inpName, std::vector<std::string> attributes) {
    name = inpName;
    header.attributes = attributes;
}

Relation::Relation(Relation* inpRelation) {
    this->name = inpRelation->name;
    this->header = inpRelation->header;

    for (Tuple t : inpRelation->tuples) {
        this->AddTuple(t);
    }
}

void Relation::SetValues(std::string inpName, std::vector<std::string> attributes) {
    name = inpName;
    header.attributes = attributes;
}

Relation* Relation::SelectVal(int index, std::string val) {
    Relation* newRelation = new Relation(name, header.attributes);
    newRelation->hasVars = hasVars;

    for (Tuple t : tuples) {
        if (t.At(index) == val) {
            newRelation->AddTuple(t);
        }
    }

    return newRelation;
}

Relation* Relation::SelectSame(int firstIndex, int secondIndex) {
    Relation* newRelation = new Relation(name, header.attributes);
    newRelation->hasVars = hasVars;

    for (Tuple t : tuples) {
        if (t.At(firstIndex) == t.At(secondIndex)) {
            newRelation->AddTuple(t);
        }
    }

    return newRelation;
}

Relation* Relation::Project(std::vector<int> indices) {
    Relation* newRelation = new Relation(name, header.attributes);
    newRelation->hasVars = hasVars;

    for (Tuple t : tuples) {
        std::vector<std::string> vals = t.GetValues();
        Tuple newTuple(vals);
        
        for (int i = 0; i < (int)vals.size(); i++) {
            if (std::count(indices.begin(), indices.end(), i) == 0) {
                newTuple.RemoveAt(i);
            }
        }

        newRelation->AddTuple(newTuple);
    }

    for (int i = 0; i < (int)newRelation->header.attributes.size(); i++) {
        if (std::count(indices.begin(), indices.end(), i) == 0) {
            newRelation->header.attributes.erase(newRelation->header.attributes.begin() + i);
        }
    }
    
    return newRelation;
}

Relation* Relation::Rename(std::vector<std::string> attributes) {
    Relation* newRelation = new Relation(name, header.attributes);
    newRelation->hasVars = hasVars;

    for (Tuple t : tuples) {
        newRelation->AddTuple(t);
    }

    int attributeNum = attributes.size();
    for (int i = 0; i < attributeNum; i++) {
        newRelation->header.attributes.at(i) = attributes.at(i);
    }

    return newRelation;
}

void Relation::AddTuple(Tuple tuple) {
    tuples.insert(tuple);
}

std::string Relation::ToString() {
    std::stringstream os;

    if (tuples.size() > 0) {
        os << " Yes(" << tuples.size() << ")";
    }
    else {
        os << " No";
    }

    if (hasVars) {
        for (Tuple t : tuples) {
            os << std::endl << "  ";
            for (int i = 0; i < t.Size(); i++) {
                os << header.attributes.at(i) << "=" << t.At(i);
                if (i < t.Size() - 1) os << ", ";
            }
        }
    }

    return os.str();
}