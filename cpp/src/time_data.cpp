#include <stdint.h>
#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <iomanip>
#include <fstream>
#include "misc.hpp"
#include "time_data.hpp"

using std::vector;
using std::complex;

dsp::TimeData::TimeData(double t_step_, vector<complex<double>> bins_):
t_step{t_step_},
bins{bins_}
{

}
dsp::TimeData::TimeData(audio_decode::AudioData data) {
    this->t_step = 1/data.sample_rate;
    
    vector<complex<double>> tmp(data.samples.begin(), data.samples.end());
    this->bins = tmp;
}

void dsp::TimeData::to_csv(std::string filepath, std::string form) {
    std::ofstream out_file;
	out_file.open(filepath);

    if (form == "complex") {
        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->t_step << "," << this->bins[i] << "\n";
        }
    }
    else if (form == "real") {
        vector<double> re_bins = this->re();

        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->t_step << "," << re_bins[i] << "\n";
        }
    }
    else if (form == "imaginary") {
        vector<double> im_bins = this->im();

        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->t_step << "," << im_bins[i] << "\n";
        }
    }
    else if (form == "magnitude") {
        vector<double> mag_bins = this->mag();

        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->t_step << "," << mag_bins[i] << "\n";
        }
    }
    else if (form == "phase") {
        vector<double> phase_bins = this->arg();

        for (size_t i = 0; i < this->bins.size(); i++) {
            out_file << std::fixed << std::setprecision(15);
            out_file << i*this->t_step << "," << phase_bins[i] << "\n";
        }
    }
    else {
        throw std::runtime_error(
            "dsp::FrequencyData::to_csv: form must be either \"complex\", \"magnitude\", \"real\", \"imaginary\", or \"phase\"");
    }

	out_file.close();
}

std::vector<double> dsp::TimeData::mag() { return dsp::mag(this->bins); }
std::vector<double> dsp::TimeData::arg() { return dsp::arg(this->bins); }
std::vector<double> dsp::TimeData::re() { return dsp::re(this->bins); }
std::vector<double> dsp::TimeData::im() { return dsp::im(this->bins); }

