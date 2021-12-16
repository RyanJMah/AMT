#pragma once
#include <stdint.h>
#include <vector>

class AudioData {
    public:
        AudioData(double sample_rate, uint32_t bit_depth, std::vector<int32_t> samples);

    public:
        double sample_rate;
        uint32_t bit_depth;
        std::vector<int32_t> samples;
};
