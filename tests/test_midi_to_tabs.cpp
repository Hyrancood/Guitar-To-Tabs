#include <doctest/doctest.h>
#include "midi_to_tabs/midi_to_tabs.hpp"
#include <stdexcept>

TEST_CASE("read_triplets valid cases") {
    SUBCASE("basic input") {
        std::istringstream input("1 2 3\n4 5 6\nstop\n");
        auto result = read_triplets(input);
        CHECK(result.size() == 2);
        CHECK(result[0] == std::array<int,3>{1,2,3});
        CHECK(result[1] == std::array<int,3>{4,5,6});
    }

    SUBCASE("empty") {
        std::istringstream input("stop\n");
        auto result = read_triplets(input);
        CHECK(result.empty());
    }
}

TEST_CASE("read_triplets exceptions") {
    SUBCASE("not enough numbers") {
        std::istringstream input("1 2\n"); 
        CHECK_THROWS_AS(read_triplets(input), std::invalid_argument);
    }
    SUBCASE("not a number") {
        std::istringstream input2("1 a 3\n"); 
        CHECK_THROWS_AS(read_triplets(input2), std::invalid_argument);
    }
}