#pragma once

#include <vector>
#include <functional>
#include "dsp.hpp"

namespace amt {
    dsp::TimeData onset_detection(dsp::TimeData data, double t_hop, std::function<double(double)> weighing_func);
}
