#pragma once
#include <vector>
#include <utility>
#include <sstream>
#include <array>

const std::array<int, 6> strings_midi = {64, 59, 55, 50, 45, 40};
const int MAX_WIDTH = 100;

std::vector<std::array<int, 3>> read_range(std::istream& in);
std::vector<std::array<int, 3>> apply_range(std::vector<std::array<int, 3>> ranges, std::vector<std::pair<int, int>> midi_beats);
void generate_tab(std::vector<std::array<int, 3>>& notes, std::ostream& out);