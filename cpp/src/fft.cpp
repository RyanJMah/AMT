#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <algorithm>
#include "frequency_data.hpp"
#include "misc.hpp"
#include "fft.hpp"

using std::vector;
using std::complex;

// mathematical constants
static complex<double> operator"" _j(long double d) {
    return complex<double>{0.0, static_cast<double>(d)};
}
static const double PI = std::atan(1)*4;
static const complex<double> J = 1.0_j;

vector<complex<double>> dsp::_fft_recursive(vector<complex<double>> x) {
    size_t N = x.size();

    // base case
    if (N == 1) {
        // The DFT of a signal of size 1 is equal to the signal itself...
        vector<complex<double>> X = {x[0]};
        return X;
    }

    // recursive case
    else {
        // separate the odd and even bins
        vector<complex<double>> even(N/2);
        vector<complex<double>> odd(N/2);

        for (size_t i = 0; i < N/2; i += 2) {
            even[i/2] = x[i];
            odd[i/2] = x[i + 1];
        }

        vector<complex<double>> E = dsp::_fft_recursive(even);
        vector<complex<double>> O = dsp::_fft_recursive(odd);

        // calculate the fft X...
        vector<complex<double>> X(N);
        double N_ = static_cast<double>(N);
        for (size_t k = 0; k < N/2; k++) {
            
            double k_ = static_cast<double>(k);

            complex<double> W = std::exp( (-2*PI*J*k_)/N_ );

            X[k] = E[k] + W*O[k];
            X[k + N/2] = E[k] - W*O[k];
        }
        return X;
    }
}

vector<complex<double>> dsp::fft(vector<complex<double>> x) {
    // zero padding
    while (!IS_POWER_OF_TWO(x.size())) {
        x.push_back(0.0);
    }

    vector<complex<double>> X = dsp::_fft_recursive(x);

    double N = X.size();
    auto normalize = [N](complex<double> n) -> complex<double> {
        return n/N;
    };

    vector<complex<double>> ret;
    std::transform(X.begin(), X.end(), std::back_inserter(ret), normalize);

    return ret;
}
dsp::FrequencyData dsp::fft_with_metadata(dsp::TimeData data) {
    using namespace dsp;

    vector<complex<double>> x = data.bins;

    vector<complex<double>> X = fft(x);

    double sample_rate = 1/data.t_step;
    double f_step = sample_rate/x.size();

    return FrequencyData(f_step, X);
}

vector<dsp::FrequencyData> dsp::sftp(dsp::TimeData data, double t_hop) {
    // convert the t_hop to number of bins to hop
    uint32_t bin_hop = t_hop/data.t_step;

    double sample_rate = 1/data.t_step;
    vector<FrequencyData> results;
    size_t i;
    for (i = 0; i < data.bins.size(); i += bin_hop) {
        vector<complex<double>> slice_t_domain(&data.bins[i], &data.bins[i + bin_hop - 1]);
        vector<complex<double>> windowed_slice = dsp::hann_window(slice_t_domain);

        vector<complex<double>> slice_f_domain = dsp::fft(slice_t_domain);
        double f_step = sample_rate/slice_t_domain.size();

        results.push_back(FrequencyData(f_step, slice_f_domain));
    }

    // assure that all of the signal is converted...
    if (i < data.bins.size()) {
        vector<complex<double>> slice_t_domain(&data.bins[i], &data.bins[data.bins.size() - 1]);
        vector<complex<double>> windowed_slice = dsp::hann_window(slice_t_domain);

        vector<complex<double>> slice_f_domain = dsp::fft(slice_t_domain);
        double f_step = sample_rate/slice_t_domain.size();

        results.push_back(FrequencyData(f_step, slice_f_domain));
    }

    return results;
}