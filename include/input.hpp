#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include "minimp3.h" // Предполагая, что вы используете minimp3 для декодирования MP3

class AudioDecoder {
public:
    struct AudioData {
        std::vector<float> samples;
        int sampleRate;
        int channels;
        size_t totalSamples;
    };
    AudioDecoder();
    AudioData loadMP3(const std::string& filename);
private:
    struct MP3DecoderDeleter {
        void operator()(mp3dec_t* decoder) const;
    };
    std::unique_ptr<mp3dec_t, MP3DecoderDeleter> mp3Decoder;
};

class AudioAnalyzer {
public:
    struct AmplitudeAnalysis {
        std::vector<float> amplitudes;
        float maxAmplitude;
        float minAmplitude;
        float averageAmplitude;
        std::vector<float> amplitudeSpectrum;
    };
    static AmplitudeAnalysis analyzeAmplitudes(const std::vector<float>& samples, int channels);
    static void printAnalysisReport(const AmplitudeAnalysis& analysis);
    static void visualizeWaveform(const std::vector<float>& amplitudes, size_t width = 80, size_t height = 20);
private:
    static void computeSimpleSpectrum(AmplitudeAnalysis& analysis);
};

class AudioProcessor {
public:
    std::vector<float> processFile(const std::string& inputFile);
};
