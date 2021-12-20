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

        public:
            double f_step;
            std::vector<std::complex<double>> bins;
    };

    std::vector<double> mag(std::vector<std::complex<double>> x);
    std::vector<double> arg(std::vector<std::complex<double>> x);
}

