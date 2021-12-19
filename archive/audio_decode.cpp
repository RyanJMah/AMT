#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <cassert>
#include <boost/python.hpp>
#include "audio_decode.hpp"

BOOST_PYTHON_MODULE(audio_decode) {
    boost::python::def("decode_wav", audio_decode_PyWrappers::decode_wav);
}

boost::python::tuple audio_decode_PyWrappers::decode_wav(std::string filepath) {
    AudioData data = audio_decode::decode_wav(filepath);

    boost::python::list ret_list;
    for (size_t i = 0; i < data.samples.size(); i++) { ret_list.append(data.samples[i]); }

    return boost::python::make_tuple(data.sample_rate, data.bit_depth, ret_list);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// audio_decode
AudioData audio_decode::decode_wav(std::string filepath) {
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
    uint8_t format = _decode_little_endian(raw_data, indx + FORMAT_START, indx + FORMAT_END);

    if (format != 1) {
        throw std::runtime_error("audio_decode::decode_wav: only PCM format is supported");
    }

    // get the number of channels
    uint32_t num_channels = _decode_little_endian(
        raw_data, indx + NUM_CHANNELS_START, indx + NUM_CHANNELS_END);

    // get the sample rate
    uint32_t sample_rate = _decode_little_endian(
        raw_data, indx + SAMPLE_RATE_START, indx + SAMPLE_RATE_END);

    // get the bit depth
    uint32_t bit_depth = _decode_little_endian(
        raw_data, indx + BIT_DEPTH_START, indx + BIT_DEPTH_END);

    std::cout << "num_channels = " << num_channels << std::endl;
    std::cout << "sample_rate = " << sample_rate << std::endl;
    std::cout << "bit_depth = " << bit_depth << std::endl;

    // go to the data section
    std::vector<uint8_t> data_ = {'d','a','t', 'a'};
    it = std::search(raw_data.begin(), raw_data.end(), data_.begin(), data_.end());
    indx = std::distance(raw_data.begin(), it) + data_.size();
    indx += SAMPLES_START;

    assert( (bit_depth % 8) == 0 );
    uint32_t byte_step = bit_depth/8;

    // this entire section below this comment is super sketchy... TOO BAD!
    std::vector<int32_t> samples;
    if (num_channels == 1) {
        samples.resize( (raw_data.size() - indx)/byte_step + 5);		// + 5 to be safe
        for (std::size_t j = 0; indx < raw_data.size(); j++) {
            samples[j] = (int16_t)_decode_little_endian(raw_data, indx, (indx + byte_step - 1));
            indx += byte_step;
        }
    }
    else if (num_channels == 2) {
        // +5 to be safe
        uint32_t size = static_cast<uint32_t>(( (raw_data.size() - indx)/byte_step )/2 + 5);
        samples.resize(size);

        for (size_t j = 0; indx < raw_data.size(); j++) {
            int16_t left = _decode_little_endian(raw_data, indx, (indx + byte_step - 1));
            int16_t right = _decode_little_endian(raw_data, indx + byte_step, (indx + byte_step*2) - 1);

            samples[j] = (left + right)/2;
            // std::cout << indx << "\n";
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

    return file_data;
}

size_t audio_decode::_decode_big_endian(std::vector<uint8_t> data, size_t start, size_t end) {
    size_t decoded_data = 0;
    for (size_t i = end - 1, j = 0; i >= start; i--, j += 8) {
        decoded_data |= (uint32_t)(data[i] << j);
    }
    return decoded_data;
}

size_t audio_decode::_decode_little_endian(std::vector<uint8_t> data, size_t start, size_t end) {
    ssize_t decoded_data = 0;
    for (size_t i = start, j = 0; i <= end - 1; i++, j += 8) {
        decoded_data += (uint32_t)(data[i] << j);
    }
    return decoded_data;
}

std::string audio_decode::_uint_to_ascii(size_t num) {
    std::string str = "";
    while (num > 0) {
        str += (uint8_t)(num & 0xFF);
        num = num >> 8;
    }
    std::reverse(str.begin(), str.end());
    return str;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////


