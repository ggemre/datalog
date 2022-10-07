#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

class Tuple {
    private:
        std::vector<std::string> values;
    public:
        bool operator< (const Tuple &rhs) const {
            return values < rhs.values;
        }
};

#endif // TUPLE_H