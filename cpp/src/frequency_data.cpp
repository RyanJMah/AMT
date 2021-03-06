#include <stdint.h>
#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <iomanip>
#include <fstream>
#include "misc.hpp"
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
    else if (form == "real") {
        vector<double> re_bins = this->re();

        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->f_step << "," << re_bins[i] << "\n";
        }
    }
    else if (form == "imaginary") {
        vector<double> im_bins = this->im();

        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->f_step << "," << im_bins[i] << "\n";
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
            "dsp::FrequencyData::to_csv: form must be either \"complex\", \"magnitude\", \"real\", \"imaginary\", or \"phase\"");
    }

	out_file.close();
}
vector<double> dsp::FrequencyData::mag() { return dsp::mag(this->bins); }
vector<double> dsp::FrequencyData::arg() { return dsp::arg(this->bins); }
vector<double> dsp::FrequencyData::re() { return dsp::re(this->bins); }
vector<double> dsp::FrequencyData::im() { return dsp::im(this->bins); }
