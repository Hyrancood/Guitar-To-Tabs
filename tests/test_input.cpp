#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include "input.hpp"
#include <vector>
#include <cmath>
#include <fstream>

// Вспомогательная функция для создания временного WAV-файла с синусоидой
void create_test_mp3(const std::string& filename, float freq = 440.0f, int sampleRate = 44100, float duration = 0.1f) {
    // Для реального теста нужен настоящий mp3-файл. Здесь только заглушка.
    // В реальных CI-тестах используйте заранее подготовленный короткий mp3-файл.
}

TEST_CASE("AudioDecoder выбрасывает исключение при отсутствии файла") {
    AudioDecoder decoder;
    CHECK_THROWS_AS(decoder.loadMP3("nonexistent_file.mp3"), std::runtime_error);
}

TEST_CASE("AudioAnalyzer корректно анализирует амплитуды для синусоиды") {
    // Генерируем синусоиду
    float freq = 440.0f;
    int sampleRate = 44100;
    float duration = 0.01f;
    int N = static_cast<int>(sampleRate * duration);
    std::vector<float> samples(N);
    for (int i = 0; i < N; ++i) {
        samples[i] = std::sin(6.283 * freq * i / sampleRate);
    }
    auto analysis = AudioAnalyzer::analyzeAmplitudes(samples, 1);
    CHECK(analysis.amplitudes.size() == samples.size());
    CHECK(analysis.maxAmplitude <= 1.0f);
    CHECK(analysis.minAmplitude >= -1.0f);
    CHECK(analysis.averageAmplitude > 0.0f);
}

TEST_CASE("AudioAnalyzer корректно работает с многоканальным сигналом") {
    // Стерео: левый канал — синусоида, правый — нули
    int N = 1000;
    std::vector<float> samples(N * 2);
    for (int i = 0; i < N; ++i) {
        samples[2 * i] = std::sin(6.283 * 440.0f * i / N);
        samples[2 * i + 1] = 0.0f;
    }
    auto analysis = AudioAnalyzer::analyzeAmplitudes(samples, 2);
    CHECK(analysis.amplitudes.size() == N);
    for (float v : analysis.amplitudes) {
        CHECK(v <= 1.0f);
        CHECK(v >= -1.0f);
    }
}

TEST_CASE("AudioAnalyzer считает спектр амплитуд") {
    std::vector<float> samples(1000);
    for (int i = 0; i < 1000; ++i) samples[i] = std::sin(6.283 * 440.0f * i / 1000);
    auto analysis = AudioAnalyzer::analyzeAmplitudes(samples, 1);
    CHECK(analysis.amplitudeSpectrum.size() == 20);
    for (float v : analysis.amplitudeSpectrum) {
        CHECK(v >= 0.0f);
    }
}