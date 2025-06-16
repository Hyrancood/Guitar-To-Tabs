#include "pitch_detector.hpp"
#include <vector>
#include <cmath>
#include <limits>

// Реализация YIN-алгоритма для pitch detection
std::vector<PitchResult> PitchDetector::detectYIN(const std::vector<float>& signal, float sampleRate, int windowSize, int hopSize, float threshold) {
    std::vector<PitchResult> results;
    size_t N = signal.size();
    for (size_t start = 0; start + windowSize < N; start += hopSize) {
        // 1. Difference function
        std::vector<float> diff(windowSize, 0.0f);
        for (int tau = 1; tau < windowSize; ++tau) {
            float sum = 0.0f;
            for (int i = 0; i < windowSize - tau; ++i) {
                float d = signal[start + i] - signal[start + i + tau];
                sum += d * d;
            }
            diff[tau] = sum;
        }
        // 2. Cumulative mean normalized difference
        std::vector<float> cmnd(windowSize, 0.0f);
        cmnd[0] = 1.0f;
        float runningSum = 0.0f;
        for (int tau = 1; tau < windowSize; ++tau) {
            runningSum += diff[tau];
            cmnd[tau] = diff[tau] / ((runningSum / tau) + 1e-8f);
        }
        // 3. Absolute minimum below threshold
        int tauEstimate = -1;
        for (int tau = 2; tau < windowSize; ++tau) {
            if (cmnd[tau] < threshold) {
                // Local minimum
                while (tau + 1 < windowSize && cmnd[tau + 1] < cmnd[tau]) ++tau;
                tauEstimate = tau;
                break;
            }
        }
        float freq = 0.0f;
        if (tauEstimate > 0) {
            freq = sampleRate / tauEstimate;
        }
        results.push_back({freq, start, static_cast<size_t>(windowSize)});
    }
    return results;
}
