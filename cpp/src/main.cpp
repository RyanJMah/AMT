#include <iostream>
#include "audio_data.hpp"
#include "audio_decode.hpp"
#include "dsp.hpp"

int main();

int main() {
    // AudioData data = audio_decode::decode_wav("../samples/Chopin_Nocturne_Op_32 No_2_in_A-flat_Major.wav");
    // audio_decode::AudioData data = audio_decode::decode_wav("../samples/Piano_A_440.wav");
    audio_decode::AudioData data = audio_decode::decode_wav("../samples/Sine_Wave_A_440.wav");

    std::cout << "data.sample_rate = " << data.sample_rate << std::endl;
    std::cout << "data.bit_depth = " << data.bit_depth << std::endl;
    std::cout << "data.samples.size() = " << data.samples.size() << std::endl;

    dsp::FrequencyData f_data = dsp::fft_with_metadata(data);

    data.to_csv("../time_domain.csv");
    f_data.to_csv("../freq_domain_complex.csv", "complex");
    f_data.to_csv("../freq_domain_mag.csv", "magnitude");
    f_data.to_csv("../freq_domain_phase.csv", "phase");

    return 0;
}
