#pragma once
#include <stdint.h>
#include <vector>
#include <string>

namespace audio_decode {
    class AudioData {
        public:
            AudioData(double sample_rate_, uint32_t bit_depth_, std::vector<int32_t> samples_);
            void to_csv(std::string filepath);

        public:
            double sample_rate;
            uint32_t bit_depth;
            std::vector<int32_t> samples;
    };
}

