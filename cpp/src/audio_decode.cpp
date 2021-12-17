#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "Python.h"
#include "audio_decode.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// AudioDecode
AudioData AudioDecode::decode_wav(std::string filepath) {
    std::vector<uint8_t> raw_hex = AudioDecode::_read_file(filepath);

    double sample_rate = AudioDecode::_decode_little_endian(
        raw_hex, WAV_SAMPLE_RATE_START, WAV_SAMPLE_RATE_END);

    uint32_t bit_depth = AudioDecode::_decode_little_endian(
        raw_hex, WAV_BIT_DEPTH_START, WAV_BIT_DEPTH_END);

    unsigned int channels = AudioDecode::_decode_little_endian(
        raw_hex, WAV_NUM_CHANNELS_START, WAV_NUM_CHANNELS_END);

    // end of the "format" (fmt) section
    size_t i = WAV_BIT_DEPTH_END;
    while (
        AudioDecode::_uint_to_ascii(AudioDecode::_decode_big_endian(raw_hex, i, i + 3)) != "data" ) { i++; }

    // skip over the "data" and "chunk size" fields
    i += 8;


    // prepare to extract the samples
    assert( (bit_depth % 8) == 0 );
    unsigned int byte_step = bit_depth/8;

    // this entire section below this comment is super sketchy... TOO BAD!
    std::vector<int32_t> samples;
    if (channels == 1) {
        samples.resize( (raw_hex.size() - i)/byte_step + 5);		// + 5 to be safe
        for (std::size_t j = 0; i < raw_hex.size(); j++) {
            samples[j] = (int16_t)AudioDecode::_decode_little_endian(raw_hex, i, (i + byte_step - 1));
            i += byte_step;
        }
    }
    else {
        samples.resize( ( (raw_hex.size() - i)/byte_step )/2 + 5 );	// + 5 to be safe
        for (ssize_t j = 0; i < raw_hex.size(); j++) {
            int16_t left = AudioDecode::_decode_little_endian(raw_hex, i, (i + byte_step - 1));
            int16_t right = AudioDecode::_decode_little_endian(raw_hex, i + byte_step, (i + byte_step*2) - 1);

            samples[j] = (left + right)/2;
            i += byte_step*2;
        }
    }
    return AudioData(sample_rate, bit_depth, samples);
}

std::vector<uint8_t> AudioDecode::_read_file(std::string filepath) {
    std::streampos file_size;
    std::ifstream file(filepath, std::ios::binary);

    file.seekg(0, std::ios::end);
    file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> file_data(file_size);
    file.read((char*) &file_data[0], file_size);

    return file_data;
}

size_t AudioDecode::_decode_big_endian(std::vector<uint8_t> data, size_t start, size_t end) {
    size_t decoded_data = 0;
    for (size_t i = end, j = 0; i >= start; i--, j += 8) {
        decoded_data |= (uint32_t)(data[i] << j);
    }
    return decoded_data;
}

size_t AudioDecode::_decode_little_endian(std::vector<uint8_t> data, size_t start, size_t end) {
    ssize_t decoded_data = 0;
    for (size_t i = start, j = 0; i <= end; i++, j += 8) {
        decoded_data += (uint32_t)(data[i] << j);
    }
    return decoded_data;
}

std::string AudioDecode::_uint_to_ascii(size_t num) {
    std::string str = "";
    while (num > 0) {
        str += (uint8_t)(num & 0xFF);
        num = num >> 8;
    }
    std::reverse(str.begin(), str.end());
    return str;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////


