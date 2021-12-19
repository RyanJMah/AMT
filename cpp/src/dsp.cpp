#include <stdint.h>
#include <stddef.h>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "dsp.hpp"

using std::vector;
using std::complex;

// mathematical constants
static complex<double> operator"" _j(long double d) {
    return complex<double>{0.0, static_cast<double>(d)};
}
static const double PI = std::atan(1)*4;
static const complex<double> J = 1.0_j;

dsp::FrequencyData::FrequencyData(double f_step_, vector<complex<double>> bins_):
f_step{f_step_},
bins{bins_}
{

}
void dsp::FrequencyData::to_csv(std::string filepath, std::string form) {
    std::ofstream out_file;
	out_file.open(filepath);

    if (form == "complex") {
        for (std::size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->f_step << "," << this->bins[i] << "\n";
        }
    }
    else if (form == "magnitude") {
        vector<double> mag_bins = this->mag();

        for (std::size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->f_step << "," << mag_bins[i] << "\n";
        }
    }
    else if (form == "phase") {
        vector<double> phase_bins = this->arg();

        for (std::size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->f_step << "," << phase_bins[i] << "\n";
        }
    }
    else {
        throw std::runtime_error(
            "dsp::FrequencyData::to_csv: form must be either \"complex\", \"magnitude\", or \"phase\"");
    }

	out_file.close();
}
vector<double> dsp::FrequencyData::mag() { return dsp::mag(this->bins); }
vector<double> dsp::FrequencyData::arg() { return dsp::arg(this->bins); }

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
        vector<complex<double>> even;
        vector<complex<double>> odd;
        even.resize(N/2);
        odd.resize(N/2);

        for (size_t i = 0; i < N/2; i += 2) {
            even[i/2] = x[i];
            odd[i/2] = x[i + 1];
        }

        vector<complex<double>> E = dsp::_fft_recursive(even);
        vector<complex<double>> O = dsp::_fft_recursive(odd);

        // calculate the fft X...
        vector<complex<double>> X;
        X.resize(N);
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
dsp::FrequencyData dsp::fft_with_metadata(audio_decode::AudioData data) {
    using namespace dsp;

    vector<complex<double>> x(data.samples.begin(), data.samples.end());

    vector<complex<double>> X = fft(x);
    double f_step = data.sample_rate/X.size();

    return FrequencyData(f_step, X);
}

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
