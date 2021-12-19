#pragma once
#include <stdint.h>
#include <vector>
#include <boost/python.hpp>

class AudioData {
    public:
        AudioData(double sample_rate, uint32_t bit_depth, std::vector<int32_t> samples);
        void test();

    public:
        double sample_rate;
        uint32_t bit_depth;
        std::vector<int32_t> samples;
};

namespace audio_data_PyWrappers {
    AudioData make_AudioData(double sample_rate, uint32_t bit_depth, boost::python::list samples);
};

