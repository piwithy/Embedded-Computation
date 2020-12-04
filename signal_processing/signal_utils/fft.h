//
// Created by salyd on 04/12/2020.
//

#ifndef SIGNAL_PROCESSING_FFT_H
#define SIGNAL_PROCESSING_FFT_H

#include <vector>
#include <numbers>
#include "common.h"

void v_rect_dit_fft(std::vector<Complex> &x) {
    using namespace std::complex_literals;
    auto x_size = x.size();

    if (x_size <= 1)
        return;

    std::vector<Complex> odd;
    std::vector<Complex> even;

    // decimation odd / even
    std::copy_if(x.cbegin(), x.cend(), std::back_inserter(odd),
                 [n = 0](Complex c)mutable { return ((n++) % 2) != 0; });
    odd.shrink_to_fit();
    std::copy_if(x.cbegin(), x.cend(), std::back_inserter(even),
                 [n = 0](Complex c)mutable { return ((n++) % 2) == 0; });
    even.shrink_to_fit();
    v_rect_dit_fft(odd);
    v_rect_dit_fft(even);

    for (auto k = 0; k < x_size / 2; k++) {
        Complex t = std::exp(-2. * 1i * std::numbers::pi * ((double) k / x_size)) * odd[k];
        x[k] = even[k] + t;
        x[x_size / 2 + k] = even[k] - t;
    }

}

void v_rect_dit_fft_array(Complex *x, std::size_t x_size) {
    using namespace std::complex_literals;

    if (x_size <= 1)
        return;

    Complex odd[x_size / 2];
    Complex even[x_size / 2];

    // decimation odd / even
    for (auto idx = 0; idx < x_size / 2; idx++) {
        even[idx] = x[2 * idx];
        odd[idx] = x[2 * idx + 1];
    }

    v_rect_dit_fft_array(odd, x_size / 2);
    v_rect_dit_fft_array(even, x_size / 2);

    for (auto k = 0; k < x_size / 2; k++) {
        Complex t = std::exp(-2. * 1i * std::numbers::pi * ((double) k / x_size)) * odd[k];
        x[k] = even[k] + t;
        x[x_size / 2 + k] = even[k] - t;
    }

}

void ite_dit_fft_array(Complex *x, std::size_t x_size){

}

#endif //SIGNAL_PROCESSING_FFT_H
