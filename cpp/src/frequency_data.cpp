#include <stdint.h>
#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <iomanip>
#include <fstream>
#include "frequency_data.hpp"

using std::vector;
using std::complex;

dsp::FrequencyData::FrequencyData(double f_step_, vector<complex<double>> bins_):
f_step{f_step_},
bins{bins_}
{

}
void dsp::FrequencyData::to_csv(std::string filepath, std::string form) {
    std::ofstream out_file;
	out_file.open(filepath);

    if (form == "complex") {
        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->f_step << "," << this->bins[i] << "\n";
        }
    }
    else if (form == "magnitude") {
        vector<double> mag_bins = this->mag();

        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->f_step << "," << mag_bins[i] << "\n";
        }
    }
    else if (form == "phase") {
        vector<double> phase_bins = this->arg();

        for (size_t i = 0; i < this->bins.size(); i++) {
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
