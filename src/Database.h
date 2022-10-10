#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include <string>
#include "Relation.h"

#include <sstream>

class Database {
    public:
        std::map<std::string, Relation*> entries;

        std::string ToString() {
            std::stringstream os;
            for (std::pair<std::string, Relation*> entry : entries) {
                os << entry.first << " " << entry.second->ToString() << std::endl;
            }
            return os.str();
        }
};

#endif // DATABASE_H