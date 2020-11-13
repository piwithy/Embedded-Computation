#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
private:
    double inf;
    double sup;

public:
    Interval();

    Interval(double, double);

    Interval(double);

    double getInf() const;

    double getSup() const;

};

#endif
