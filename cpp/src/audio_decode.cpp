#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cassert>
#include "audio_decode.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// audio_decode
audio_decode::AudioData audio_decode::decode_wav(std::string filepath) {
    using namespace audio_decode;

    // read the file
    std::vector<uint8_t> raw_data = _read_file(filepath);

    // make sure that it's a .wav file
    std::vector<uint8_t> RIFF = {'R','I','F','F'};
    auto it = std::search(raw_data.begin(), raw_data.end(), RIFF.begin(), RIFF.end());
    size_t indx = std::distance(raw_data.begin(), it) + RIFF.size();

    if (indx >= raw_data.size()) {
        throw std::runtime_error("audio_decode::decode_wav: provided file is not of WAV format");
    }

    // goto the header section
    std::vector<uint8_t> fmt = {'f','m','t', 0x20};
    it = std::search(raw_data.begin(), raw_data.end(), fmt.begin(), fmt.end());
    indx = std::distance(raw_data.begin(), it) + fmt.size();

    // assure that the file is PCM format
    uint8_t format = _decode_little_endian(
        &raw_data[indx + FORMAT_START], &raw_data[indx + FORMAT_END]);

    if (format != 1) {
        throw std::runtime_error("audio_decode::decode_wav: only PCM format is supported");
    }

    // get the number of channels
    uint32_t num_channels = _decode_little_endian(
        &raw_data[indx + NUM_CHANNELS_START], &raw_data[indx + NUM_CHANNELS_END]);

    // get the sample rate
    uint32_t sample_rate = _decode_little_endian(
        &raw_data[indx + SAMPLE_RATE_START], &raw_data[indx + SAMPLE_RATE_END]);

    // get the bit depth
    uint32_t bit_depth = _decode_little_endian(
        &raw_data[indx + BIT_DEPTH_START], &raw_data[indx + BIT_DEPTH_END]);

    if (bit_depth != 16) {
        throw std::runtime_error(
            "audio_decode::decode_wav: only files with a bit depth of 16 are currently supported");
    }

    // go to the data section
    std::vector<uint8_t> data_ = {'d','a','t', 'a'};
    it = std::search(raw_data.begin(), raw_data.end(), data_.begin(), data_.end());
    indx = std::distance(raw_data.begin(), it) + data_.size();

    size_t data_size = _decode_little_endian(
        &raw_data[indx + DATA_SIZE_START], &raw_data[indx + DATA_SIZE_END]);

    indx += SAMPLES_START;

    uint32_t byte_step = bit_depth/8;

    // this entire section below this comment is super sketchy... TOO BAD!
    std::vector<int32_t> samples;
    if (num_channels == 1) {
        samples.resize(data_size/byte_step);		// + 5 to be safe
        for (size_t j = 0; j < samples.size(); j++) {
            samples[j] = _decode_little_endian(&raw_data[indx], &raw_data[indx + byte_step]);
            indx += byte_step;
        }
    }
    else if (num_channels == 2) {
        samples.resize(static_cast<uint32_t>(data_size/byte_step/2));     // +5 to be safe

        for (size_t j = 0; j < samples.size(); j++) {
            int16_t left = static_cast<int16_t>(
                _decode_little_endian(&raw_data[indx], &raw_data[indx + byte_step]) );
            int16_t right = static_cast<int16_t>(
                _decode_little_endian(&raw_data[indx + byte_step], &raw_data[indx + byte_step*2]) );

            samples[j] = (left + right)/2;
            indx += byte_step*2;
        }
    }
    else {
        throw std::runtime_error("audio_decode::decode_wav: number of channels is greater than 2");
    }

    return AudioData(static_cast<double>(sample_rate), bit_depth, samples);
}

std::vector<uint8_t> audio_decode::_read_file(std::string filepath) {
    if (!std::filesystem::exists(filepath)) {
        throw std::runtime_error("audio_decode::_read_file: file does not exist...");
    }

    std::streampos file_size;
    std::ifstream file(filepath, std::ios::binary);

    file.seekg(0, std::ios::end);
    file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> file_data(file_size);
    file.read((char*) &file_data[0], file_size);

    file.close();

    return file_data;
}

uint32_t audio_decode::_decode_little_endian(uint8_t* begin, uint8_t* end) {
	uint32_t ret = 0;
    size_t shift = 0;
    for (uint8_t* p = begin; p != end; p++) {
        ret |= (*p << shift);
        shift += 8;
    }
    return ret;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
