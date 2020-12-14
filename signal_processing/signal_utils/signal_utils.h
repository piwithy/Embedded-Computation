//
// Created by jezegoup on 23/11/2020.
//

#ifndef SIGNAL_PROCESSING_SIGNAL_UTILS_H
#define SIGNAL_PROCESSING_SIGNAL_UTILS_H

#ifndef SIGNAL_PROCESSING_COMMON_H

#include "common.h"

#endif

#include <vector>
#include <array>


constexpr std::array<double, N> rect_window();

constexpr std::array<double, N> cosine_window(double a0);

constexpr std::array<double, N> hann_window();

constexpr std::array<double, N> hamming_window();

constexpr std::array<double, N> blackman_window();

template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v);

std::vector<double> makeTimeVector(double Fs, std::size_t size);

std::vector<double> makeFrequencyVector(double Fs, std::size_t size);

template<typename T>
std::vector<T> makeSinusVector(const std::vector<double> &time, double f);

template<typename T>
std::vector<T> makeAMSinusVector(const std::vector<double> &time, double fp, double fm);


std::vector<double> psd(const std::vector<Complex> &dft);


std::vector<double> toReal(const std::vector<Complex> &x);

template<typename Tcontainer, typename Tsignal>
std::vector<Tcontainer> generate_random_vector(Tsignal inf, Tsignal sup, std::size_t size);


template<typename F,
        typename ... Args>
Duration::rep wall_time_profile(F &&fun, Args &&... args);

template<typename F,
        typename ... Args>
Duration::rep cpu_time_profile(F &&fun, Args &&... args);

std::pair<typename std::chrono::milliseconds::rep, typename std::chrono::milliseconds::rep>
average_stddev(const std::vector<typename std::chrono::milliseconds::rep> &data);

template<typename F,
        typename ... Args>
Duration::rep wall_time_average_profile(std::size_t nRuns, F &&fun, Args &&... args);


template<typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &s, const std::array<T, SIZE> &a);


template<typename T>
std::tuple<bool, int, double> epsilon_vector_compare(const std::string &title, std::vector<T> x, std::vector<T> y);

template<typename F,
        typename ... Args>
void peakDetection(const std::string &title, double Fs, std::vector<Complex> &signal, F &&fun, Args &&... args);

void windowing(const std::array<double, N> &w, std::vector<Complex> &s);

#include "signal_utils.tpp"

#endif //SIGNAL_PROCESSING_SIGNAL_UTILS_H
