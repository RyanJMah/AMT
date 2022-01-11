#pragma once
#include <stdint.h>
#include <vector>
#include <string>

// I know I should probably be inheriting from something here, but I'm also lazy so too bad

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

