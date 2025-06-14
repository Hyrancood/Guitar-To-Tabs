#include "midi_to_tabs/midi_to_tabs.hpp"
#include <array>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <sstream>

std::vector<std::array<int, 3>> read_triplets(std::istream& in) {
    std::vector<std::array<int, 3>> result;
    std::string line;

    while (std::getline(in, line)) {
        if (line == "stop") {
            break;
        }
        std::istringstream iss(line);
        std::array<int, 3> triplet;
        if (!(iss >> triplet[0] >> triplet[1] >> triplet[2])) {
            throw std::invalid_argument("Failed to parse triplet: " + line);
        }
        result.push_back(triplet);
    }
    return result;
}