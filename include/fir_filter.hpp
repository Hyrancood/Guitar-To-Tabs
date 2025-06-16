#pragma once
#include <vector>

class FIRFilter {
public:
    // Применяет скользящее среднее (FIR-фильтр) к сигналу
    // windowSize - размер окна усреднения
    static std::vector<float> apply(const std::vector<float>& input, int windowSize);
};
