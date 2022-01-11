#include <vector>
#include <complex>
#include <functional>
#include "dsp.hpp"
#include "onset_detection.hpp"

using std::vector;
using std::complex;

dsp::TimeData amt::onset_detection(dsp::TimeData data, double t_hop, std::function<double(double)> weighing_func) {
    vector<dsp::FrequencyData> sftp_results = dsp::sftp(data, t_hop);

    vector<complex<double>> detection_curve(sftp_results.size());
    for (size_t i = 0; i < detection_curve.size(); i++) {
        double sum = 0;
        for (size_t f = 0; f < detection_curve.size(); f++) {
            complex<double> bin = sftp_results[i].bins[f];
            sum += std::pow(std::abs(bin), 2)*(weighing_func(f));
        }

        detection_curve[i] = sum;
    }
    return dsp::TimeData(t_hop, detection_curve);
}
