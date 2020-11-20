#include <iostream>
#include <numbers>
#include <sstream>
#include "../src/Interval.h"
#include "../src/EmptyIntervalException.h"
#include "catch.hpp"


TEST_CASE("Interval Constructors", "[interval]") {
    SECTION("Default constructor") {
        Interval i;
        REQUIRE(std::isnan(i.getInf()));
        REQUIRE(std::isnan(i.getSup()));
        REQUIRE(i.isNan());
    }

    SECTION("Parameter constructor", "[interval]") {
        Interval i(-2, 3);
        REQUIRE(-2 == i.getInf());
        REQUIRE(3 == i.getSup());
        REQUIRE(!i.isNan());
    }

    SECTION("Parameter constructor, degenerated interval", "[interval]") {
        Interval i(-2);
        REQUIRE(-2 == i.getInf());
        REQUIRE(-2 == i.getSup());
        REQUIRE(!i.isNan());
    }

    SECTION("Copy constructor", "[interval]") {
        Interval i(-5, 42.);
        Interval ip(i);
        REQUIRE(i.getInf() == ip.getInf());
        REQUIRE(i.getSup() == ip.getSup());
        REQUIRE(!i.isNan());
    }

    SECTION("Move constructor", "[interval]") {
        Interval i(-5, 42.);
        Interval ip = std::move(i);
        REQUIRE(-5 == ip.getInf());
        REQUIRE(42. == ip.getSup());
        REQUIRE(!ip.isNan());
        REQUIRE(i.isNan());
    }

}

TEST_CASE("Interval Functions", "[interval]") {
    SECTION("isEmpty() function", "[interval]") {
        Interval j;
        REQUIRE(j.isEmpty());
        Interval i(-2);
        REQUIRE_FALSE(i.isEmpty());
        Interval k(-2, 3);
        REQUIRE_FALSE(k.isEmpty());
        Interval l(4, -1);
        REQUIRE(l.isEmpty());
        Interval m(NAN, 3);
        REQUIRE(m.isEmpty());
        Interval n(NAN, NAN);
        REQUIRE(n.isEmpty());
        Interval o(-2, NAN);
        REQUIRE(o.isEmpty());
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE_FALSE(oo.isEmpty());
    }

    SECTION("width() function", "[interval]") {
        Interval i(-2);
        REQUIRE(i.width() == 0);
        Interval j(1, 7);
        REQUIRE(j.width() == 6);
        Interval k(-5, 7);
        REQUIRE(k.width() == 12);
        Interval l(6, -2);
        REQUIRE_THROWS_AS(l.width(), EmptyIntervalException);
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE(oo.width() == std::numeric_limits<double>::infinity());
    }

    SECTION("isDegenerated() function", "[interval]") {
        Interval i(-2);
        REQUIRE(i.isDegenerated());
        Interval j;
        REQUIRE_FALSE(j.isDegenerated());
        Interval k(-5, 7);
        REQUIRE_FALSE(k.isDegenerated());
        Interval l(6, -2);
        REQUIRE_FALSE(l.isDegenerated());
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE_FALSE(oo.isDegenerated());
        Interval om(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
        REQUIRE(om.isDegenerated());
        Interval op(std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE(op.isDegenerated());
    }

}

TEST_CASE("Interval Friends", "[interval]") {
    SECTION("<< operator", "[interval]") {
        // EMPTY
        Interval j;
        std::ostringstream os;
        os << j;
        std::string result = os.str();
        REQUIRE(result == "Empty Interval");
        // DEGENERATED
        Interval i(2);
        os.str(""); // clear stream
        os << i;
        result = os.str();
        REQUIRE(result == "Degenerated Interval : [2]");
        // NORMAL
        Interval k(-5.8, 4.7);
        os.str(""); // clear stream
        os << k;
        result = os.str();
        REQUIRE(result == "[-5.8, 4.7]");
        // Infinity
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        os.str(""); // clear stream
        os << oo;
        result = os.str();
        REQUIRE(result == "[-inf, inf]");
    }

    SECTION("== operator", "[interval]") {
        Interval i(-2);
        Interval j(1);
        REQUIRE_FALSE(i == j);
        Interval k(1, 4);
        Interval l(2, 3);
        REQUIRE_FALSE(k == l);
        Interval m(-1, 4);
        Interval n(-1, 4);
        REQUIRE(m == n);
        Interval e;
        REQUIRE_FALSE(e == m);
        Interval ee;
        REQUIRE_FALSE(e == ee);
        Interval f(7, -3);
        Interval g(7, -3);
        REQUIRE(f == g);
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        Interval om(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
        REQUIRE_FALSE(oo == om);
    }
    SECTION("Inter() function", "[interval]") {
        Interval i(-2);
        Interval j(1);
        REQUIRE(Inter(i, j).isEmpty());
        REQUIRE((i & j).isEmpty());
        Interval k(1, 4);
        Interval l(2, 3);
        REQUIRE(Inter(k, l) == Interval(2, 3));
        REQUIRE((k & l) == Interval(2, 3));
        Interval m(-1, 4);
        Interval n(2, 7);
        REQUIRE(Inter(m, n) == Interval(2, 4));
        REQUIRE((m & n) == Interval(2, 4));
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE(Inter(oo, n) == n);
        REQUIRE(Inter(m, oo) == m);
        REQUIRE((oo & n) == n);
        REQUIRE((m & oo) == m);
    }
    SECTION("Union() function", "[interval]") {
        Interval i(-2);
        Interval j(1);
        REQUIRE(Union(i, j) == Interval(-2, 1));
        REQUIRE((i | j) == Interval(-2, 1));
        Interval k(1, 4);
        Interval l(2, 3);
        REQUIRE(Union(k, l) == Interval(1, 4));
        REQUIRE((k | l) == Interval(1, 4));
        Interval m(-1, 4);
        Interval n(2, 7);
        REQUIRE(Union(m, n) == Interval(-1, 7));
        REQUIRE((m | n) == Interval(-1, 7));
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE(Union(oo, n) == oo);
        REQUIRE(Union(n, oo) == oo);
        REQUIRE((oo | n) == oo);
        REQUIRE((n | oo) == oo);
    }
    SECTION("+ operator", "[interval]") {
        Interval i(-2);
        Interval j(1);
        REQUIRE(i + j == Interval(-1));
        Interval k(1, 4);
        Interval l(2, 3);
        REQUIRE(k + 6 == Interval(7, 10));
        REQUIRE(2 + l == Interval(4, 5));
        REQUIRE(k + l == Interval(3, 7));
        Interval m(-1, 4);
        Interval n(-1, 4);
        REQUIRE(m + n == Interval(-2, 8));
        Interval e;
        REQUIRE((e + m).isEmpty());
        Interval ee;
        REQUIRE((ee + e).isEmpty());
        Interval f(7, -3);
        Interval g(7, -3);
        REQUIRE((f + g).isEmpty());
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE(oo + oo == oo);
        Interval om(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
        REQUIRE((oo + om).isEmpty());
    }
    SECTION("- operator", "[interval]") {
        Interval h(2);
        Interval i(-2);
        REQUIRE(h == -i);
        Interval j(1);
        REQUIRE(i - j == Interval(-3));
        Interval k(1, 4);
        Interval l(2, 3);
        REQUIRE(k - 6 == Interval(-5, -2));
        REQUIRE(2 - l == Interval(-1, 0));
        REQUIRE(k - l == Interval(-2, 2));
        Interval m(-1, 4);
        Interval n(-3, 7);
        REQUIRE(m - n == Interval(-8, 7));
        REQUIRE(n - m == Interval(-7, 8));
        Interval e;
        REQUIRE((e - m).isEmpty());
        Interval ee;
        REQUIRE((ee - e).isEmpty());
        Interval f(7, -3);
        Interval g(7, -3);
        REQUIRE((f - g).isEmpty());
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE(oo - oo == oo);
        Interval om(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
        REQUIRE((oo - om).isEmpty());
    }
    SECTION("* operator", "[interval]") {
        Interval i(-2);
        Interval j(1);
        REQUIRE(i * j == Interval(-2));
        Interval k(1, 4);
        Interval l(2, 3);
        REQUIRE(k * 6 == Interval(6, 24));
        REQUIRE(2 * l == Interval(4, 6));
        REQUIRE(k * l == Interval(2, 12));
        Interval m(-1, 4);
        Interval n(-3, 7);
        REQUIRE(m * n == Interval(-12, 28));
        Interval e;
        REQUIRE((e * m).isEmpty());
        Interval ee;
        REQUIRE((ee * e).isEmpty());
        Interval f(7, -3);
        Interval g(7, -3);
        REQUIRE((f * g).isEmpty());
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        REQUIRE(oo * oo == oo);
        Interval om(-std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
        REQUIRE((oo * om) == oo);
    }
    SECTION("/ operator", "[interval]") {
        Interval i(-2);
        Interval j(1);
        REQUIRE(i / j == Interval(-2));
        Interval oo(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
        Interval k(1, 4);
        REQUIRE((j / k) == Interval(1.0 / 4, 1));
        REQUIRE((k / j) == Interval(1, 4));
        Interval l(2, 3);
        REQUIRE(k / 6 == Interval(1.0 / 6, 2.0 / 3));
        REQUIRE(2 / l == Interval(2.0 / 3, 1));
        REQUIRE(k / l == Interval(1.0 / 3, 2));
        Interval m(-1, 4);
        Interval n(-3, 7);
        REQUIRE(m / n == oo);
        Interval e;
        REQUIRE((e / m).isEmpty());
        Interval ee;
        REQUIRE((ee / e).isEmpty());
        Interval f(7, -3);
        Interval g(7, -3);
        REQUIRE((f / g).isEmpty());
        REQUIRE((oo / oo) == oo);
        Interval om(-std::numeric_limits<double>::infinity());
        REQUIRE((oo / om).isEmpty());
    }
}