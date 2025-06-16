#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "PitchDetector.hpp"
#include <vector>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

std::vector<float> generate_sine(float freq, float sampleRate, float duration) {
    int N = static_cast<int>(sampleRate * duration);
    std::vector<float> data(N);
    for (int i = 0; i < N; ++i) {
        data[i] = static_cast<float>(std::sin(2 * M_PI * freq * i / sampleRate));
    }
    return data;
}

TEST_CASE("PitchDetector::detectYIN находит частоту синусоиды 440 Гц") {
    float freq = 440.0f;
    float sampleRate = 44100.0f;
    auto signal = generate_sine(freq, sampleRate, 0.1f);
    int windowSize = 2048;
    int hopSize = 512;
    auto results = PitchDetector::detectYIN(signal, sampleRate, windowSize, hopSize);
    // Проверяем, что большинство окон дают частоту близкую к 440 Гц
    int count = 0;
    for (const auto& r : results) {
        if (r.frequency > 0.0f)
            CHECK(std::abs(r.frequency - 440.0f) < 5.0f);
        if (r.frequency > 0.0f) ++count;
    }
    CHECK(count > 5); // Должно быть несколько окон с определённой частотой
}

TEST_CASE("PitchDetector::detectYIN возвращает 0 на тишине") {
    std::vector<float> silence(44100, 0.0f);
    auto results = PitchDetector::detectYIN(silence, 44100.0f, 2048, 512);
    for (const auto& r : results) {
        CHECK(r.frequency == doctest::Approx(0.0f));
    }
}
