//
// Created by salyd on 07/12/2020.
//

#ifndef SIGNAL_PROCESSING_STFT_H
#define SIGNAL_PROCESSING_STFT_H

#include "../common.h"
#include <vector>
#include <array>

std::tuple<std::vector<std::vector<Complex>>, std::vector<double>, std::vector<double>>
process_signal(const std::vector<float> &x);

std::tuple<double, double> compute_avg_stddev(const std::vector<Complex> &x);

std::tuple<std::vector<double>, std::vector<double>>
compute_avg_stddev(const std::vector<std::vector<Complex>> &bins);

#endif //SIGNAL_PROCESSING_STFT_H
