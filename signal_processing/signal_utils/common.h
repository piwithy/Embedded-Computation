//
// Created by jezegoup on 23/11/2020.
//

#ifndef SIGNAL_PROCESSING_COMMON_H
#define SIGNAL_PROCESSING_COMMON_H

#include <complex>
#include <chrono>
#include <array>
#include <numbers>

typedef std::complex<double> Complex;
constexpr size_t N = 512;
constexpr size_t KiB = 1024;
constexpr size_t MiB = 1024 * KiB;
constexpr size_t GiB = 1024 * MiB;
typedef std::chrono::microseconds Duration;

template<std::size_t DIM>
constexpr std::array<std::size_t, DIM> bit_reverse_array() {
    std::array<std::size_t, DIM> scrambled{};
    for (std::size_t i = 0; i < DIM; i++) {
        /*std::size_t j = i;
         *
         * j = (((j & 0xaaaaaaaa) >> 1) | ((j & 0x55555555) << 1));
         * j = (((j & 0xcccccccc) >> 2) | ((j & 0x33333333) << 2));
         * j = (((j & 0xf0f0f0f0) >> 4) | ((j & 0x0f0f0f0f) << 4));
         * j = (((j & 0xff00ff00) >> 8) | ((j & 0x00ff00ff) << 8));
         * j = ((j >> 16) | (j << 16)) >> (32 - m);
         */
        std::size_t j = 0;
        std::size_t b = i;
        std::size_t m = std::log2(DIM);
        while (m > 0) {
            j = j << 1;
            j = j + (b & 1);
            b = b >> 1;
            m--;
        }
        if (i < j) {
            scrambled[i] = j;
        } else
            scrambled[i] = i;
    }
    return scrambled;
}

template<std::size_t DIM>
constexpr std::array<Complex, DIM / 2> twiddle_factors() {
    std::array<Complex, DIM / 2> t;
    for (std::size_t k = 0; k < DIM / 2; k++)
        t[k] = std::exp(Complex(0, -2 * std::numbers::pi * k / DIM));
    return t;
}

#endif //SIGNAL_PROCESSING_COMMON_H
