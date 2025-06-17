#pragma once
#include <vector>

#include "pitch_detector.hpp"

struct NoteSegment {
  float frequency;
  float duration;  // в секундах
};

// freqTolerance — частоты считаются одинаковыми, если разница меньше этого
// значения (Гц)
std::vector<NoteSegment> extract_note_segments(
    const std::vector<PitchResult>& pitches, float sampleRate,
    float freqTolerance = 1.0f);
