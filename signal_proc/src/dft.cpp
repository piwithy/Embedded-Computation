//
// Created by jezegoup on 23/11/2020.
//
#include "dft.h"

std::vector<double> naive_dft(const std::vector<double> &x) {
    auto x_size = x.size();
    std::vector<double> dft(x_size);
    for (auto k = 0; k < x_size - 1; k++) {
        for (auto n = 0; n < x_size - 1; n++) {

        }
    }
    return dft;
}
