#include <stdint.h>
#include <stddef.h>
#include <vector>
#include <complex>
#include "frequency_data.hpp"
#include "pitch_detection.hpp"

using std::vector;
using std::complex;

dsp::FrequencyData amt::harmonic_product_spectrum(dsp::FrequencyData data, uint32_t num_harmonics) {
    vector<complex<double>> x = data.bins;
    size_t N = x.size();

    vector<complex<double>> Y(N);

    for (size_t i = 0; i < (N/num_harmonics); i++) {
        complex<double> product = x[i];
        for (size_t n = 1; n <= num_harmonics; n++) {
            product *= x[i*n];
        }
        Y[i] = product;
    }

    return dsp::FrequencyData(data.f_step, Y);
}
