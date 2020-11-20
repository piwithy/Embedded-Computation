#ifndef FT_GLOBAL_H
#define FT_GLOBAL_H

#include <cstddef>
#include <complex>
#include <vector>
#include <iterator>
#include <array>

constexpr size_t N = 256;
typedef std::complex<double> Complex;

std::vector<double> makeTimeVector(double Fs, std::size_t size);

std::vector<double> makeFrequencyVector(double Fs, std::size_t size);

template<typename T>
std::vector<T> makeSinusVector(const std::vector<double> &time, double f);

template<typename T>
std::vector<T> makeAMSinusVector(const std::vector<double> &time, double fp, double fm);

constexpr std::array<Complex, N> rect_window();

constexpr std::array<Complex, N> cosine_window(double a0);

constexpr std::array<Complex, N> hann_window();

constexpr std::array<Complex, N> hamming_window();

constexpr std::array<Complex, N> blackman_window();

template<typename T>
std::vector<T> generate_random_vector(double inf, double sup, std::size_t size);

std::vector<double> toReal(const std::vector<Complex> &x);

std::vector<double> toImag(const std::vector<Complex> &x);

std::vector<Complex> toComplex(const std::vector<double> &x);

double sin(double f, double t, double phi = 0);

void windowing(const std::array<double, N> &w, std::vector<Complex> &s);

std::vector<double> psd(const std::vector<Complex> &dft);



#include "common.tpp"

#endif //FT_GLOBAL_H