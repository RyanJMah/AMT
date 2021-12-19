#pragma once

#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <string>
#include "audio_data.hpp"

namespace audio_decode {
    AudioData decode_wav(std::string filepath);

    std::vector<uint8_t> _read_file(std::string filepath);

    uint32_t _decode_big_endian(uint8_t* begin, uint8_t* end);
    uint32_t _decode_little_endian(uint8_t* begin, uint8_t* end);

    typedef enum {
        FORMAT_START = 4,
        FORMAT_END = 6,

        NUM_CHANNELS_START = 6,
        NUM_CHANNELS_END = 8,

        SAMPLE_RATE_START = 8,
        SAMPLE_RATE_END = 12,

        BIT_DEPTH_START = 18,
        BIT_DEPTH_END = 20,

        DATA_SIZE_START = 0,
        DATA_SIZE_END = 4,

        SAMPLES_START = 4
    } WAVFormatOffsets;
};
