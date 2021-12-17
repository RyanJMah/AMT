#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <stddef.h>
#include "audio_data.hpp"

#define WAV_NUM_CHANNELS_START 22
#define WAV_NUM_CHANNELS_END 23

#define WAV_SAMPLE_RATE_START 24
#define WAV_SAMPLE_RATE_END 27

#define WAV_BIT_DEPTH_START 34
#define WAV_BIT_DEPTH_END 35

namespace AudioDecode {
    AudioData decode_wav(std::string filepath);

    std::vector<uint8_t> _read_file(std::string filepath);
    size_t _decode_big_endian(std::vector<uint8_t> data, size_t start, size_t end);
    size_t _decode_little_endian(std::vector<uint8_t> data, size_t start, size_t end);
    std::string _uint_to_ascii(size_t num);
};

