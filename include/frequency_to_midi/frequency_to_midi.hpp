#pragma once
#include <vector>
#include <utility>

const int min_midi = 40;
const int max_midi = 86;

struct NoteDuration {
    size_t num;
    int midi;
    double duration = 0.0;
};

int frequency_to_midi(double freq);
double duration_sum(const std::vector<NoteDuration>& midi_duration);
int max_duration(const std::vector<NoteDuration>& midi_duration);
std::vector<std::pair<int, int>> get_midi_beats(std::vector<std::pair<double, double>> frequency_duration, int bpm);
