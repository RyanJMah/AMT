#pragma once

#include <vector>
#include <complex>
#include <string>
#include "audio_data.hpp"

#define IS_POWER_OF_TWO(n) ( n && ((n & (n - 1)) == 0) )

namespace dsp {
    class FrequencyData {
        public:
            FrequencyData(double f_step_, std::vector<std::complex<double>> bins_);
            void to_csv(std::string filestepm, std::string form);

            std::vector<double> mag();
            std::vector<double> arg();

        public:
            double f_step;
            std::vector<std::complex<double>> bins;
    };

    std::vector<std::complex<double>> _fft_recursive(std::vector<std::complex<double>> x);

    std::vector<std::complex<double>> fft(std::vector<std::complex<double>> x);
    FrequencyData fft_with_metadata(audio_decode::AudioData data);

    std::vector<double> mag(std::vector<std::complex<double>> x);
    std::vector<double> arg(std::vector<std::complex<double>> x);
}
