#include <iostream>
#include "../src/Interval.h"
#include "catch.hpp"


TEST_CASE("Interval Constructors", "[interval]") {

    SECTION("Default constructor") {
        Interval i;
        REQUIRE(std::isnan(i.getInf()));
        REQUIRE(std::isnan(i.getSup()));
    }

    SECTION("Parameter constructor", "[interval]") {
        Interval i(-2, 3);
        REQUIRE(-2 == i.getInf());
        REQUIRE(3 == i.getSup());
    }

    SECTION("Parameter constructor, degenerated interval", "[interval]") {
        Interval i(-2);
        REQUIRE(-2 == i.getInf());
        REQUIRE(-2 == i.getSup());
    }

}
