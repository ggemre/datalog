#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

class Tuple {
    private:
        std::vector<std::string> values;
    public:
        Tuple(std::vector<std::string> inpValues) {
            values = inpValues;
        }

        void SetValues(std::vector<std::string> inpValues) {
            values = inpValues;
        }

        std::vector<std::string> GetValues() {
            return values;
        }

        std::string At(int index) {
            return values.at(index);
        }

        void RemoveAt(int index) {
            values.erase(values.begin() + index);
        }

        int Size() {
            return values.size();
        }

        bool operator< (const Tuple &rhs) const {
            return values < rhs.values;
        }
};

#endif // TUPLE_H