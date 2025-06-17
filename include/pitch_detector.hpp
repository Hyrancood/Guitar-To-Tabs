#pragma once
#include <cstddef>
#include <vector>

// Структура для хранения результата pitch detection
struct PitchResult {
  float frequency;     // Гц
  size_t startSample;  // индекс первого сэмпла окна
  size_t length;       // длина окна в сэмплах
};

class PitchDetector {
 public:
  // YIN-алгоритм для извлечения основного тона
  // signal: входной сигнал (моно)
  // sampleRate: частота дискретизации
  // windowSize: размер окна (обычно 1024-2048)
  // hopSize: шаг окна (обычно 256-512)
  // threshold: порог для YIN (0.1-0.2)
  static std::vector<PitchResult> detectYIN(const std::vector<float>& signal,
                                            float sampleRate, int windowSize,
                                            int hopSize,
                                            float threshold = 0.15f);
};
