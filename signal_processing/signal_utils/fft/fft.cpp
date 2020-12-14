//
// Created by salyd on 04/12/2020.
//

#include "fft.h"

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

    for (std::size_t k = 0; k < x_size / 2; k++) {
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
    for (std::size_t idx = 0; idx < x_size / 2; idx++) {
        even[idx] = x[2 * idx];
        odd[idx] = x[2 * idx + 1];
    }

    v_rect_dit_fft_array(odd, x_size / 2);
    v_rect_dit_fft_array(even, x_size / 2);

    for (std::size_t k = 0; k < x_size / 2; k++) {
        Complex t = std::exp(-2. * 1i * std::numbers::pi * ((double) k / x_size)) * odd[k];
        x[k] = even[k] + t;
        x[x_size / 2 + k] = even[k] - t;
    }

}

void ite_dit_fft(std::vector<Complex> &x) {
    std::size_t problemSize = x.size();
    std::size_t stages = std::log2(problemSize);
    auto tf = twiddle_factors<N>();

    bit_reverse_reorder(x);

    for (std::size_t stage = 0; stage <= stages; stage++) {
        std::size_t currentSize = 1 << stage;
        std::size_t step = stages - stage;
        std::size_t halfSize = currentSize / 2;
        for (std::size_t k = 0; k < problemSize; k = k + currentSize) {
            for (std::size_t j = 0; j < halfSize; j++) {
                auto u = x[k + j];
                auto v = x[k + j + halfSize] * tf[j * (1 << step)];
                x[k + j] = (u + v);
                x[k + j + halfSize] = (u - v);
            }
        }
    }
}

void ite_dit_fft_array(Complex *x, std::size_t x_size) {
    std::size_t problemSize = x_size;
    std::size_t stages = std::log2(problemSize);
    auto tf = twiddle_factors<N>();

    bit_reverse_reorder(x, x_size);

    for (std::size_t stage = 0; stage <= stages; stage++) {
        std::size_t currentSize = 1 << stage;
        std::size_t step = stages - stage;
        std::size_t halfSize = currentSize / 2;
        for (std::size_t k = 0; k < problemSize; k = k + currentSize) {
            for (std::size_t j = 0; j < halfSize; j++) {
                auto u = x[k + j];
                auto v = x[k + j + halfSize] * tf[j * (1 << step)];
                x[k + j] = (u + v);
                x[k + j + halfSize] = (u - v);
            }
        }
    }
}

void v_rect_dif_fft(std::vector<Complex> &x) {
    using namespace std::complex_literals;
    std::size_t x_size = x.size();

    if (x_size <= 1)
        return;

    std::vector<Complex> left(x_size / 2);
    std::vector<Complex> right(x_size / 2);

    // decimation left / right
    for (std::size_t idx = 0; idx < x_size / 2; idx++) {
        left[idx] = x[idx];
        right[idx] = x[(x_size / 2) + idx];
    }

    for (std::size_t k = 0; k < x_size / 2; k++) {
        auto tmp = left[k];
        left[k] = left[k] + right[k];
        right[k] = (tmp - right[k]) * std::exp(-2. * 1i * std::numbers::pi * ((double) k / x_size));
    }

    v_rect_dif_fft(left);
    v_rect_dif_fft(right);

    std::size_t j = 0;
    for (std::size_t k = 0; k < x_size / 2; k++) {
        x[j] = left[k];
        x[j + 1] = right[k];
        j += 2;
    }
}

void v_rect_dif_fft_array(Complex *x, std::size_t x_size) {
    using namespace std::complex_literals;

    if (x_size <= 1)
        return;

    Complex left[x_size / 2];
    Complex right[x_size / 2];

    // decimation left / right
    for (std::size_t idx = 0; idx < x_size / 2; idx++) {
        left[idx] = x[idx];
        right[idx] = x[(x_size / 2) + idx];
    }

    for (std::size_t k = 0; k < x_size / 2; k++) {
        auto tmp = left[k];
        left[k] = left[k] + right[k];
        right[k] = (tmp - right[k]) * std::exp(-2. * 1i * std::numbers::pi * ((double) k / x_size));
    }

    v_rect_dif_fft_array(left, x_size / 2);
    v_rect_dif_fft_array(right, x_size / 2);

    std::size_t j = 0;
    for (std::size_t k = 0; k < x_size / 2; k++) {
        x[j] = left[k];
        x[j + 1] = right[k];
        j += 2;
    }
}

void ite_dif_fft(std::vector<Complex> &x) {
    auto w = twiddle_factors<N>();
    std::size_t problemSize = x.size(), numOfProblem = 1;

    while (problemSize > 1) {
        std::size_t halfSize = problemSize / 2;
        for (std::size_t k = 0; k < numOfProblem; k++) {
            std::size_t jFirst = k * problemSize, jLast = jFirst + halfSize - 1, jTwiddle = 0;
            for (std::size_t j = jFirst; j <= jLast; j++) {
                auto W = w[jTwiddle];
                auto temp = x[j];
                x[j] = temp + x[j + halfSize];
                x[j + halfSize] = W * (temp - x[j + halfSize]);
                jTwiddle += numOfProblem;
            }
        }
        numOfProblem *= 2;
        problemSize = halfSize;
    }
    bit_reverse_reorder(x);
}

void ite_dif_fft_array(Complex *x, size_t x_size) {
    auto w = twiddle_factors<N>();
    std::size_t problemSize = x_size, numOfProblem = 1;

    while (problemSize > 1) {
        std::size_t halfSize = problemSize / 2;
        for (std::size_t k = 0; k < numOfProblem; k++) {
            std::size_t jFirst = k * problemSize, jLast = jFirst + halfSize - 1, jTwiddle = 0;
            for (std::size_t j = jFirst; j <= jLast; j++) {
                auto W = w[jTwiddle];
                auto temp = x[j];
                x[j] = temp + x[j + halfSize];
                x[j + halfSize] = W * (temp - x[j + halfSize]);
                jTwiddle += numOfProblem;
            }
        }
        numOfProblem *= 2;
        problemSize = halfSize;
    }
    bit_reverse_reorder(x, x_size);
}


void bit_reverse_reorder(std::vector<Complex> &W) {
    constexpr std::array<std::size_t, N> scrambled = bit_reverse_array<N>();
    for (std::size_t i = 0; i < W.size(); i++) {
        std::size_t j = scrambled[i];
        if (i < j) {
            swap(W[i], W[j]);
        }
    }
}

void bit_reverse_reorder(Complex *W, std::size_t len) {
    constexpr std::array<std::size_t, N> scrambled = bit_reverse_array<N>();
    for (std::size_t i = 0; i < len; i++) {
        std::size_t j = scrambled[i];
        if (i < j) {
            swap(W[i], W[j]);
        }
    }
}