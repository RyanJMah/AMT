#include <vector>
#include <complex>
#include <cmath>
#include <algorithm>
#include "misc.hpp"

using std::vector;
using std::complex;

static const double PI = std::atan(1)*4;

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

vector<complex<double>> dsp::hann_window(vector<complex<double>> x) {
    vector<complex<double>> ret(x.size());

    for (size_t i = 0; i < x.size(); i++) {
        complex<double> multiplier = 0.5*( 1 - std::cos(2*PI*i/(x.size() - 1)) );
        ret[i] = multiplier*x[i];
    }

    return ret;
}
