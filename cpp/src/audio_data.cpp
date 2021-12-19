#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "audio_data.hpp"

AudioData::AudioData(double sample_rate_, uint32_t bit_depth_, std::vector<int32_t> samples_):
sample_rate{sample_rate_},
bit_depth{bit_depth_},
samples{samples_}
{
// empty
}

void AudioData::to_csv(std::string filepath) {
	std::ofstream out_file;
	out_file.open(filepath);

    double Ts = 1/this->sample_rate;

	for (std::size_t i = 0; i < this->samples.size(); i++) {
		out_file << std::fixed << std::setprecision(15);
		out_file << i*Ts << "," << this->samples[i] << "\n";
	}

	out_file.close();
}
