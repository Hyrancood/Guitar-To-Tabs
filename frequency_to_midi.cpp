#include "tabs.hpp"
#include <cmath>
#include <stdexcept>

int frequency_to_midi(double freq) {
    if (freq < 0) {
        throw std::invalid_argument("Invalid frequency");
    }

    if (freq == 0.0) {
        return -1;
    }
    
    int midi = static_cast<int>(std::round(69 + 12 * std::log2(freq / 440.0)));
    if (midi < min_midi || midi > max_midi) {
        throw std::invalid_argument("Frequency is out of guitar range");
    }

    return midi;
}

double duration_sum(const std::vector<Triple>& midi_duration) {
    double result = 0.0;
    for (Triple t : midi_duration) {
        result += t.duration;
    }
    return result;
}

int max_duration(const std::vector<Triple>& midi_duration) {
    int index_max = 0;
    for (size_t i = 0; i < midi_duration.size(); ++i) {
        if (midi_duration[i].duration > midi_duration[index_max].duration) {
            index_max = i;
        }
    }
    return index_max;
}

std::vector<std::pair<int, int>> get_midi_beats(std::vector<std::pair<double, double>> frequency_duration, int bpm) {
    if (bpm <= 0) {
        throw std::invalid_argument("BPM must be positive");
    }

    double len16 = 15.0/bpm;

    std::vector<Triple> midi_duration;
    for (size_t i = 0; i < frequency_duration.size(); ++i) {
        midi_duration.push_back({i, frequency_to_midi(frequency_duration[i].first), frequency_duration[i].second});
    }

    midi_duration.push_back({midi_duration.size(),-1,len16*2});
    std::vector<std::pair<int,int>> midi_16beats; 
    std::vector<Triple> temporary;
    double remainder = len16;
    while (midi_duration.size() > 1) {
        remainder = len16;
        temporary.clear();
        while (duration_sum(temporary) < len16) {
            if (midi_duration[0].duration > remainder) {
                midi_duration[0].duration -= remainder;
                temporary.push_back({midi_duration[0].num, midi_duration[0].midi, remainder});
                break;
            } else {
                temporary.push_back(midi_duration[0]);
                remainder -= midi_duration[0].duration;
                midi_duration.erase(midi_duration.begin());
            }
        }

        if (temporary.size() == 1) {
            midi_16beats.push_back({temporary[0].num,temporary[0].midi});
        } else {
            midi_16beats.push_back({temporary[max_duration(temporary)].num,temporary[max_duration(temporary)].midi});
        }
    }
    
    std::vector<std::pair<int,int>> midi_beats;
    for (size_t i = 0; i < midi_16beats.size(); ++i) {
        if (i!=0 && midi_16beats[i-1].first==midi_16beats[i].first) {
            midi_beats[midi_beats.size()-1].second+=1;
        } else {
            midi_beats.push_back({midi_16beats[i].second,1});
        }
    }

    return midi_beats;
}


