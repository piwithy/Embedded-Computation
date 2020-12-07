//
// Created by salyd on 04/12/2020.
//

#ifndef SIGNAL_PROCESSING_FFT_H
#define SIGNAL_PROCESSING_FFT_H

#include <vector>
#include <numbers>
#include <array>
#include <iostream>
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

void scramble(Complex *x, size_t size, std::array<std::size_t, N> cifer) {
    Complex x_scram[size];
    for (size_t idx = 0; idx < size; idx++) {
        x_scram[cifer[idx]] = x[idx];
    }
    for (size_t idx = 0; idx < size; idx++) {
        x[idx] = x_scram[idx];
    }
}


constexpr std::array<Complex, N / 2> twiddle_factors() {
    std::array<Complex, N / 2> t;
    for (std::size_t k = 0; k < N / 2; k++)
        t[k] = std::exp(Complex(0, -2 * std::numbers::pi * k / N));
    return t;
}

void ite_dit_fft_array(Complex *x, std::size_t problem_size) {
    using namespace std::complex_literals;
    int stages = std::log2(problem_size);

    //scramble
    constexpr auto scrambled = bit_reverse_array();
    for (auto i = 0; i < problem_size; i++) {
        auto j = scrambled[i];
        if (i < j)
            swap(x[i], x[j]);
    }

    Complex u, v;
    unsigned current_size, half_size;

    for (auto stage = 0; stage <= stages; stage++) {
        current_size = std::pow(2, stage);
        std::size_t step = stages - stage;
        half_size = current_size / 2;
        auto tf = twiddle_factors();
        for (auto k = 0; k < problem_size; k += current_size) {
            for (auto j = 0; j < half_size; j++) {
                u = x[k + j];
                v = x[k + j + half_size] * tf[j * (1 << step)];
                x[k + j] = u + v;
                x[k + j + half_size] = u - v;
            }
        }
    }

}

#endif //SIGNAL_PROCESSING_FFT_H
