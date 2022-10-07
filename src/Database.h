#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <map>
#include "Relation.h"

class Database {
    private:
        std::map<std::string, Relation> relations;
    public:
};

#endif // DATABASE_H