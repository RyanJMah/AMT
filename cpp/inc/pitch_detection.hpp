#pragma once

#include <stdint.h>
#include "frequency_data.hpp"

namespace dsp {
    FrequencyData harmonic_product_spectrum(FrequencyData data, uint32_t num_harmonics);
}
