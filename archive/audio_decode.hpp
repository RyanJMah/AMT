#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <stddef.h>
#include <boost/python.hpp>
#include "audio_data.hpp"

typedef enum {
    FORMAT_START = 4,
    FORMAT_END = 6,

    NUM_CHANNELS_START = 6,
    NUM_CHANNELS_END = 8,

    SAMPLE_RATE_START = 8,
    SAMPLE_RATE_END = 12,

    BIT_DEPTH_START = 18,
    BIT_DEPTH_END = 20,

    SAMPLES_START = 4
} WAVFormatOffsets;

namespace audio_decode {
    AudioData decode_wav(std::string filepath);

    std::vector<uint8_t> _read_file(std::string filepath);

    size_t _decode_big_endian(std::vector<uint8_t> data, size_t start, size_t end);
    size_t _decode_little_endian(std::vector<uint8_t> data, size_t start, size_t end);

    std::string _uint_to_ascii(size_t num);
};

namespace audio_decode_PyWrappers {
    boost::python::tuple decode_wav(std::string filepath);
}
