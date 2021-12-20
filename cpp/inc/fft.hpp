#pragma once

#include <vector>
#include <complex>
#include <string>
#include "audio_data.hpp"
#include "frequency_data.hpp"

#define IS_POWER_OF_TWO(n) ( n && ((n & (n - 1)) == 0) )

namespace dsp {
    std::vector<std::complex<double>> _fft_recursive(std::vector<std::complex<double>> x);

    std::vector<std::complex<double>> fft(std::vector<std::complex<double>> x);
    FrequencyData fft_with_metadata(audio_decode::AudioData data);
}
