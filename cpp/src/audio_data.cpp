#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>
#include <boost/python.hpp>
#include "audio_data.hpp"

BOOST_PYTHON_MODULE(audio_data) {
    using namespace boost::python;

    def("make_AudioData", &audio_data_PyWrappers::make_AudioData);
}

AudioData audio_data_PyWrappers::make_AudioData(double sample_rate, uint32_t bit_depth, boost::python::list samples) {
    std::vector<double> vec(boost::python::stl_input_iterator<double>(samples));
    return AudioData(sample_rate, bit_depth, vec);
}

AudioData::AudioData(double sample_rate, uint32_t bit_depth, std::vector<int32_t> samples) {
    this->sample_rate = sample_rate;
    this->bit_depth = bit_depth;
    this->samples = samples;
}

void AudioData::test() { std::cout << "fuck fuck fuck" << std::endl; }

