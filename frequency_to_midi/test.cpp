#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include "frequency_to_midi.hpp"
#include <stdexcept>

TEST_CASE("frequency_to_midi valid cases (exact frequencies)") {
    CHECK(frequency_to_midi(440.0) == 69);
    CHECK(frequency_to_midi(82.41) == 40);
    CHECK(frequency_to_midi(1174.7) == 86);
    CHECK(frequency_to_midi(146.83) == 50);
}

TEST_CASE("frequency_to_midi valid cases (imprecise frequencies)") {
    CHECK(frequency_to_midi(450.0) == 69);
    CHECK(frequency_to_midi(80.5) == 40);
    CHECK(frequency_to_midi(1205.7) == 86);
    CHECK(frequency_to_midi(143.0) == 50);
}

TEST_CASE("frequency_to_midi valid cases (rest)") {
    CHECK(frequency_to_midi(0.0) == -1);
}

TEST_CASE("frequency_to_midi invalid frequency (negative)") {
    CHECK_THROWS_AS(frequency_to_midi(-100.0), std::invalid_argument);s
}

TEST_CASE("frequency_to_midi invalid frequency (out of guitar range)") {
    CHECK_THROWS_AS(frequency_to_midi(10.0), std::invalid_argument);
    CHECK_THROWS_AS(frequency_to_midi(10000.0), std::invalid_argument);
}

TEST_CASE("get_midi_beats empty vector") {
    std::vector<std::pair<double, double>> input;
    int bpm = 60;
    auto result = get_midi_beats(input, bpm);
    std::vector<std::pair<int, int>> expected;
    CHECK(result == expected);
}

TEST_CASE("get_midi_beats basic case") {
    std::vector<std::pair<double, double>> input = {
        {440.0, 1.0},
        {146.83, 0.5},
        {0.0, 2.0}
        {220.0, 0.5}
    };

    int bpm = 60;
    auto result = get_midi_beats(input, bpm);

    std::vector<std::pair<int, int>> expected = {
        {69, 4},
        {50, 2},
        {-1, 8}
        {57, 2}  
    };

    CHECK(result == expected);
}

TEST_CASE("get_midi_beats odd lengths") {
    std::vector<std::pair<double, double>> input = {
        {880.0, 1.6},
        {440.0, 0.8},
        {220.0, 0.7},
        {110.0, 0.35},
        {220.0, 0.1},
        {440.0, 1.15},
        {220.0, 0.05},
        {440.0, 0.05},
        {220.0, 2.3},
        {110.0, 0.2},
        {220.0, 0.3},
        {110.0, 0.4}
    };

    int bpm = 60;
    auto result = get_midi_beats(input, bpm);

    std::vector<std::pair<int, int>> expected = {
        {81, 6},
        {69, 3},
        {57, 3},
        {45, 2},
        {69, 5},
        {57, 9},
        {45, 1},
        {57, 1},
        {45, 2}
    };

    CHECK(result == expected);
}

TEST_CASE("get_midi_beats one note repeating") {

}

TEST_CASE("get_midi_beats different bpm") {

}