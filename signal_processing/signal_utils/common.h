//
// Created by jezegoup on 23/11/2020.
//

#ifndef SIGNAL_PROCESSING_COMMON_H
#define SIGNAL_PROCESSING_COMMON_H

#include <complex>
#include <chrono>
#include <array>

typedef std::complex<double> Complex;
constexpr size_t N = 512;
typedef std::chrono::microseconds Duration;

constexpr unsigned rev(unsigned x) {
    x = (x & 0x55555555u) << 1 | (x >> 1) & 0x55555555u;
    x = (x & 0x33333333u) << 2 | (x >> 2) & 0x33333333u;
    x = (x & 0x0f0f0f0fu) << 4 | (x >> 4) & 0x0f0f0f0fu;
    x = (x << 24) | ((x & 0xff00) << 8) | ((x >> 8) & 0xff00) | (x >> 24);
    return x;
}

constexpr std::array<std::size_t, N> bit_reverse_array() {
    std::array<std::size_t, N> scrambled{};
    for (std::size_t i = 0; i < N; i++) {
//        std::size_t j = i;
//        j = (((j & 0xaaaaaaaa) >> 1) | ((j & 0x55555555) << 1));
//        j = (((j & 0xcccccccc) >> 2) | ((j & 0x33333333) << 2));
//        j = (((j & 0xf0f0f0f0) >> 4) | ((j & 0x0f0f0f0f) << 4));
//        j = (((j & 0xff00ff00) >> 8) | ((j & 0x00ff00ff) << 8));
//        j = ((j >> 16) | (j << 16)) >> (32 - m);
        std::size_t j = 0;
        std::size_t b = i;
        std::size_t m = std::log2(N);
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

#endif //SIGNAL_PROCESSING_COMMON_H
