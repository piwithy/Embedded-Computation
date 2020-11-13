#include "Interval.h"
#include <cmath>

Interval::Interval() : inf(NAN), sup(NAN) {};

Interval::Interval(double inf, double sup) : inf(inf), sup(sup) {};

Interval::Interval(double d) : inf(d), sup(d) {};


double Interval::getInf() const {
    return inf;
}

double Interval::getSup() const {
    return sup;
}
