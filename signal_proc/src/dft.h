//
// Created by jezegoup on 23/11/2020.
//

#ifndef SIGNAL_PROCESSING_DFT_H
#define SIGNAL_PROCESSING_DFT_H

#include <vector>

using namespace std::complex_literals;

template<typename T>
std::vector<Complex> naive_dft(const std::vector<T> &X) {
    auto x_size = X.size();
    std::vector<Complex> x(x_size);
    for (auto k = 0; k < x_size - 1; k++) {
        for (auto n = 0; n < x_size - 1; n++) {
            x.at(k) = x.at(k) +
                      X.at(n) * std::exp(((-2. * 1i * std::numbers::pi * (double) (k * n))) / ((double) x_size));
        }
    }
    return x;
}

#endif //SIGNAL_PROCESSING_DFT_H
