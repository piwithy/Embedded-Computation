#include "common.h"
#include <numbers>

std::vector<double> makeTimeVector(double Fs, std::size_t size) {
    std::vector<double> time_vector(size);
    std::generate(time_vector.begin(), time_vector.end(), [Fs, t = 0.]() mutable { return t++ / Fs; });
    return time_vector;
}

std::vector<double> makeFrequencyVector(double Fs, std::size_t size) {
    std::vector<double> frequency_vector(size);
    std::generate(frequency_vector.begin(), frequency_vector.end(), [Fs, f = 0]() mutable { return f++ * Fs; });
    return frequency_vector;
}

std::vector<double> toReal(const std::vector<Complex> &x) {
    std::vector<double> real_vector(x.size());
    std::transform(x.cbegin(), x.cend(), real_vector.begin(), [](Complex c) { return c.real(); });
    real_vector.shrink_to_fit();
    return real_vector;
}

std::vector<double> toImag(const std::vector<Complex> &x) {
    std::vector<double> imag_vector(x.size());
    std::transform(x.cbegin(), x.cend(), imag_vector.begin(), [](Complex c) { return c.imag(); });
    imag_vector.shrink_to_fit();
    return imag_vector;
}

std::vector<Complex> toComplex(const std::vector<double> &x) {
    std::vector<Complex> complex_vector(x.size());
    std::transform(x.cbegin(), x.cend(), complex_vector.begin(), [](double d) { return Complex(d, 0); });
    complex_vector.shrink_to_fit();
    return complex_vector;
}

double sin(double f, double t, double phi) {
    return std::sin(2 * std::numbers::pi * f * t + phi);
}

constexpr std::array<Complex, N> rect_window() {
    std::array<Complex, N> rect;
    std::generate(rect.begin(), rect.end(), []() { return Complex(1, 0); });
    return rect;
}

constexpr std::array<Complex, N> cosine_window(double a0) {
    std::array<Complex, N> cosine;
    int N_item = cosine.size();
    std::generate(cosine.begin(),
                  cosine.end(),
                  [N_item, a0, n = 0]() mutable {
                      double Re, Im = 0;
                      Re = a0 * (1 - std::cos((2 * std::numbers::pi * n++) / N_item));
                      return Complex(Re, Im);
                  });
    return cosine;
}

constexpr std::array<Complex, N> hann_window() {
    return cosine_window(0.5);
}

constexpr std::array<Complex, N> hamming_window() {
    return cosine_window(25. / 64.);
}

constexpr std::array<Complex, N> blackman_window() {
    double alpha = 0.16, a0 = (1 - alpha) / 2, a1 = 0.5, a2 = alpha / 2;
    std::array<Complex, N> blackman;
    int N_item = blackman.size();
    std::generate(blackman.begin(),
                  blackman.end(),
                  [a0, a1, a2, N_item, n = 0]() {
                      double Re, Im = 0;
                      Re = a0 - a1 * std::cos((2 * std::numbers::pi * n) / N_item) +
                           a2 * std::cos((4 * std::numbers::pi * n) / N_item);
                      return Complex(Re, Im);
                  });
    return blackman;
}

void windowing(const std::array<double, N> &w, std::vector<Complex> &s) {
    int window_size = w.size();
    std::transform(s.cbegin(), s.cend(), s.begin(),
                   [w, window_size, n = 0](Complex c) mutable { return c * w.at(n++ % window_size); });
}

std::vector<double> psd(const std::vector<Complex> &dft) {

}