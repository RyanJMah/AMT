#include <iostream>
#include "audio_data.hpp"
#include "audio_decode.hpp"

int main();

int main() {
    AudioData data = audio_decode::decode_wav("../samples/eaJ_x_Seori-It _just_is_(Feat_Keshi's_Strat).wav");

    std::cout << "data.sample_rate = " << data.sample_rate << std::endl;
    std::cout << "data.bit_depth = " << data.bit_depth << std::endl;
    std::cout << "data.samples.size() = " << data.samples.size() << std::endl;

    // for (size_t i = 0; i < data.samples.size(); i++) {
    //     std::cout << std::hex <<"samples[" << i << "] = " << data.samples[i] << std::endl;
    // }

    data.to_csv("../asdf.csv");

    return 0;
}
