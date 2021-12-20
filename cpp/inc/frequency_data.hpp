#pragma once 

#include <vector>
#include <complex>

namespace dsp {
    class FrequencyData {
        public:
            FrequencyData(double f_step_, std::vector<std::complex<double>> bins_);
            void to_csv(std::string filepath, std::string form);

            std::vector<double> mag();
            std::vector<double> arg();
            std::vector<double> re();
            std::vector<double> im();

        public:
            double f_step;
            std::vector<std::complex<double>> bins;
    };
}

