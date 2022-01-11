#pragma once

#include <stdint.h>
#include "frequency_data.hpp"

namespace amt {
    dsp::FrequencyData harmonic_product_spectrum(dsp::FrequencyData data, uint32_t num_harmonics);
}
