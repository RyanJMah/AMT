#pragma once

#include <vector>
#include <complex>

namespace dsp {
    std::vector<double> mag(std::vector<std::complex<double>> x);
    std::vector<double> arg(std::vector<std::complex<double>> x);
    std::vector<double> re(std::vector<std::complex<double>> x);
    std::vector<double> im(std::vector<std::complex<double>> x);
}
