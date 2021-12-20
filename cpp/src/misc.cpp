#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include "misc.hpp"

using std::vector;
using std::complex;

vector<double> dsp::mag(vector<complex<double>> x) {
    vector<double> ret;

    auto callback = [](complex<double> n) -> double {
        return std::abs(n);
    };
    std::transform(x.begin(), x.end(), std::back_inserter(ret), callback);

    return ret;
}

vector<double> dsp::arg(vector<complex<double>> x) {
    vector<double> ret;

    vector<double> x_mag = dsp::mag(x);
    auto it = std::max_element(x_mag.begin(), x_mag.end());
    double threshold = (*it)/10000;

    auto callback = [threshold](complex<double> n) -> double {
        if (std::abs(n) < threshold) {
            n = 0.0;
        }
        return std::arg(n);
    };
    std::transform(x.begin(), x.end(), std::back_inserter(ret), callback);

    return ret;
}

vector<double> dsp::re(vector<complex<double>> x) {
    vector<double> ret;

    auto callback = [](complex<double> n) -> double {
        return std::real(n);
    };
    std::transform(x.begin(), x.end(), std::back_inserter(ret), callback);

    return ret;
}

vector<double> dsp::im(vector<complex<double>> x) {
    vector<double> ret;

    auto callback = [](complex<double> n) -> double {
        return std::imag(n);
    };
    std::transform(x.begin(), x.end(), std::back_inserter(ret), callback);

    return ret;
}
