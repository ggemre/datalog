#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
class Parameter
{
private:
    std::string p;
public:
    Parameter(std::string inpP) {
        p = inpP;
    }

    std::string ToString() {
        return p;
    }
};

#endif // PARAMETER_H