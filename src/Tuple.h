#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <string>

#include <sstream>

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

        std::string ToString(std::vector<std::string> attributes) {
            std::stringstream os;

            int valNum = values.size();
            for (int i = 0; i < valNum; i++) {
                os << attributes.at(i) << "=";
                os << values.at(i);

                if (i < valNum - 1) {
                    os << ", ";
                }
            }
            return os.str();
        }
};

#endif // TUPLE_H