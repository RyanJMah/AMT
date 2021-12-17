#include <stdint.h>
#include <vector>
#include "audio_data.hpp"

AudioData::AudioData(double sample_rate, uint32_t bit_depth, std::vector<int32_t> samples) {
    this->sample_rate = sample_rate;
    this->bit_depth = bit_depth;
    this->samples = samples;
}

