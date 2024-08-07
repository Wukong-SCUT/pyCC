
#include "cec2013/Header.h"
#include "Function.hpp"

#ifndef CEC2013_H
#define CEC2013_H

class CEC2013: public Function{
    public:
        double evaluate(double *x);
        CEC2013(int);
    private:
        Benchmarks *fp;
};

#endif
