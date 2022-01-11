#include <iostream>
#include "audio_decode.hpp"
#include "dsp.hpp"
#include "amt.hpp"

int main();

int main() {
    // audio_decode::AudioData data_ = audio_decode::decode_wav(
    //     "../samples/Chopin_Nocturne_Op_32 No_2_in_A-flat_Major.wav");

    // audio_decode::AudioData data_ = audio_decode::decode_wav(
    //     "../samples/eaJ_x_Seori-It _just_is_(Feat_Keshi's_Strat).wav");

    // audio_decode::AudioData data_ = audio_decode::decode_wav("../samples/Piano_A_440.wav");
    // audio_decode::AudioData data_ = audio_decode::decode_wav("../samples/Sine_Wave_A_440.wav");

    // audio_decode::AudioData data_ = audio_decode::decode_wav("../samples/Piano_C_Major_Chord.wav");

    audio_decode::AudioData data_ = audio_decode::decode_wav("../samples/Piano_C_Major_Scale.wav");


    std::cout << "data.sample_rate = " << data_.sample_rate << std::endl;
    std::cout << "data.bit_depth = " << data_.bit_depth << std::endl;
    std::cout << "data.samples.size() = " << data_.samples.size() << std::endl;
    std::cout << std::endl;

    dsp::TimeData data = dsp::TimeData(data_);

    // std::cout << "running fft..." << std::endl;
    // dsp::FrequencyData f_data = dsp::fft_with_metadata(data);

    std::cout << "writing time_domain.csv..." << std::endl;
    data.to_csv("../time_domain.csv", "real");
    // f_data.to_csv("../freq_domain_complex.csv", "complex");
    // f_data.to_csv("../freq_domain_mag.csv", "magnitude");
    // f_data.to_csv("../freq_domain_phase.csv", "phase");

    // dsp::FrequencyData hps = dsp::harmonic_product_spectrum(f_data, 4);
    // hps.to_csv("../freq_domain_hps.csv", "magnitude");

    // std::cout << std::endl;
    std::cout << "running onset detection..." << std::endl;
    dsp::TimeData detection_curve = amt::onset_detection(data, 0.1, [](double k) { return k*k; });

    std::cout << "writing detection_curve.csv..." << std::endl;
    detection_curve.to_csv("../detection_curve.csv", "real");

    std::cout << std::endl;
    std::cout << "done." << std::endl;

    return 0;
}
