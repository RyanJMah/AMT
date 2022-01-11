#pragma once

#include <vector>
#include <complex>
#include <string>
#include "audio_decode.hpp"

// I know I should probably be inheriting from something here, but I'm also lazy so too bad

namespace dsp {
    class TimeData {
        public:
            TimeData(double t_step_, std::vector<std::complex<double>> bins);
            TimeData(audio_decode::AudioData data);

            void to_csv(std::string filepath, std::string form);

            std::vector<double> mag();
            std::vector<double> arg();
            std::vector<double> re();
            std::vector<double> im();

        public:
            double t_step;
            std::vector<std::complex<double>> bins;
    };
}

