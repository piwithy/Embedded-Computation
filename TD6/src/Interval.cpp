#include "Interval.h"
#include <cmath>
#include <vector>
#include "EmptyIntervalException.h"

#ifndef OSTREAM_LIB
#define OSTREAM_LIB

#include <ostream>

#endif

Interval::Interval() : inf(NAN), sup(NAN) {}

Interval::Interval(double inf, double sup) : inf(inf), sup(sup) {}

Interval::Interval(double d) : inf(d), sup(d) {}

Interval::Interval(Interval &&i) noexcept: inf(i.inf), sup(i.sup) {
    i.inf = NAN;
    i.sup = NAN;
}

double Interval::getInf() const {
    return inf;
}

double Interval::getSup() const {
    return sup;
}

Interval::~Interval() = default;

double Interval::width() const {
    if (isEmpty()) throw EmptyIntervalException();
    return sup - inf;
}

bool Interval::isEmpty() const {
    return (sup < inf) || std::isnan(inf) || std::isnan(sup);
}

bool Interval::isDegenerated() const {
    return (inf == sup);
}

bool Interval::isNan() const {
    return (std::isnan(inf) || std::isnan(sup));
}

std::ostream &operator<<(std::ostream &s, const Interval &i) {
    if (i.isEmpty())
        return s << "Empty Interval";
    if (i.isDegenerated())
        return s << "Degenerated Interval : [" << i.inf << "]";
    return s << '[' << i.inf << ", " << i.sup << ']';
}

bool operator==(const Interval &x, const Interval &y) {
    return (x.sup == y.sup) && (x.inf == y.inf);
}

Interval Interval::operator+(const Interval &y) const {
    if (isEmpty() || y.isEmpty())
        return Interval();
    return Interval(this->inf + y.inf, this->sup + y.sup);
}

Interval operator+(const Interval &x, const double &y) {
    Interval y_i(y);
    return x + y_i;
}

Interval operator+(const double &x, const Interval &y) {
    Interval x_i(x);
    return x_i + y;
}

Interval Interval::operator-(const Interval &y) const {
    if (isEmpty() || y.isEmpty())
        return Interval();
    return Interval(this->inf - y.sup, this->sup - y.inf);
}

Interval operator-(const Interval &x, const double &y) {
    Interval y_i(y);
    return x - y_i;
}

Interval operator-(const double &x, const Interval &y) {
    Interval x_i(x);
    return x_i - y;
}

Interval Interval::operator-() const {
    Interval other(0);
    return other - *this;
}

Interval operator*(const Interval &x, const double &y) {
    Interval y_i(y);
    return x * y_i;
}

Interval operator*(const double &x, const Interval &y) {
    Interval x_i(x);
    return x_i * y;
}

Interval Interval::operator*(const Interval &y) const {
    if (isEmpty() || y.isEmpty())
        return Interval();
    std::vector<double> star_vec{this->inf * y.inf, this->inf * y.sup, this->sup * y.inf, this->sup * y.sup};
    return Interval(*(std::min_element(star_vec.cbegin(), star_vec.cend())),
                    *(std::max_element(star_vec.cbegin(), star_vec.cend())));
}

Interval Interval::operator/(const Interval &y) const {
    if (isEmpty() || y.isEmpty())
        return Interval();
    if ((y.inf <= 0 && y.sup >= 0))
        return Interval(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
    Interval inv_y(1 / y.sup, 1 / y.inf);
    return *this * inv_y;
}

Interval operator/(const double &x, const Interval &y) {
    Interval x_i(x);
    return x_i / y;
}

Interval operator/(const Interval &x, const double &y) {
    Interval y_i(y);
    return x / y_i;
}

Interval Interval::operator&(const Interval &y) const {
    if (isEmpty() || y.isEmpty())       //if an interval is empty
        return Interval();
    if (this->isInsideOf(y))            // [ Y [ X ] Y ]
        return Interval(*this);
    if (y.isInsideOf(*this))         // [ X [ Y ] X ]
        return Interval(y);
    if (y.inf >= inf && y.sup >= sup)   // [ X [ ] Y ]
        return Interval(y.inf, sup);
    if (y.inf <= inf && y.sup <= sup)   // [ Y [ ] X ]
        return Interval(inf, y.sup);
    else                                // [ X ] [ Y ] OR [ Y ] [ X ]
        return Interval();
}


Interval Interval::operator|(const Interval &y) const {
    if (isEmpty() || y.isEmpty())       //if an interval is empty
        return Interval();
    if (this->isInsideOf(y))            // [ Y [ X ] Y ]
        return Interval(y);
    if (y.isInsideOf(*this))         // [ X [ Y ] X ]
        return Interval(*this);
    if (y.inf >= inf && y.sup >= sup)   // [ X [ ] Y ]
        return Interval(inf, y.sup);
    if (y.inf <= inf && y.sup <= sup)   // [ Y [ ] X ]
        return Interval(y.inf, sup);
    else                                // [ X ] [ Y ] OR [ Y ] [ X ]
        return Interval();
}

bool Interval::isInsideOf(const Interval &y) const {
    return ((inf >= y.inf) && (sup <= y.sup));
}

Union::Union(Interval &x, Interval &y) : Interval(x | y) {}

Inter::Inter(Interval &x, Interval &y) : Interval(x & y) {}
