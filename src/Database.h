#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include "Relation.h"

class Database {
    private:
        std::map<std::string, Relation> relations;
};

#endif // DATABASE_H