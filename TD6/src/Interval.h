#ifndef INTERVAL_H
#define INTERVAL_H

#ifndef OSTREAM_LIB
#define OSTREAM_LIB

#include <ostream>

#endif

class Interval {
protected:
    double inf{};
    double sup{};

public:
    Interval(); //Default constructor

    Interval(Interval &&) noexcept; // move constructor

    Interval(const Interval &) = default; // copy constructor

    Interval &operator=(const Interval &i);

    ~Interval(); // destructor

    Interval(double, double);

    explicit Interval(double);

    [[nodiscard]] double getInf() const;

    [[nodiscard]] double getSup() const;

    [[nodiscard]] double width() const;

    [[nodiscard]] bool isEmpty() const;

    [[nodiscard]] bool isDegenerated() const;

    [[nodiscard]] bool isNan() const;

    friend std::ostream &operator<<(std::ostream &, const Interval &);

    friend bool operator==(const Interval &x, const Interval &y);

    friend Interval operator+(const Interval &x, const double &y);

    friend Interval operator+(const double &x, const Interval &y);

    Interval operator+(const Interval &y) const;

    friend Interval operator-(const Interval &x, const double &y);

    friend Interval operator-(const double &x, const Interval &y);

    Interval operator-(const Interval &y) const;

    Interval operator-() const;

    friend Interval operator*(const Interval &x, const double &y);

    friend Interval operator*(const double &x, const Interval &y);

    Interval operator*(const Interval &y) const;

    friend Interval operator/(const Interval &x, const double &y);

    friend Interval operator/(const double &x, const Interval &y);

    Interval operator/(const Interval &y) const;

    Interval operator&(const Interval &y) const;

    Interval operator|(const Interval &y) const;

    [[nodiscard]] bool isInsideOf(const Interval &y) const;

};

class Inter : public Interval {
public:
    Inter(Interval &x, Interval &y);
};

class Union : public Interval {
public:
    Union(Interval &x, Interval &y);
};

#endif
