#ifndef SIGNAL_UTILS_H
#define SIGNAL_UTILS_H

#include "global.h"
#include <numbers>
#include <iostream>
#include <iterator>
#include <vector>
#include <array>
#include <random>
#include <chrono>
#include <execution>
#include <type_traits>

template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
    s << '[';
    if (!v.empty()) {
        std::copy(v.cbegin(), v.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << v.back();
    }
    return s << ']';
}

std::vector<double> makeTimeVector(double Fs, std::size_t size) {
    std::vector<double> time(size);
    double step = 1 / Fs;
    double t = -step;
    std::generate(time.begin(), time.end(), [&]() mutable -> double {
        t = t + step;
        return t;
    });
    return time;
}

std::vector<double> makeFrequencyVector(double Fs, std::size_t size) {
    std::vector<double> freq(size);
    double step = Fs / size;
    double f = -step;
    std::generate(freq.begin(), freq.end(), [&]() mutable -> double {
        f = f + step;
        return f;
    });
    return freq;
}

template<typename T>
std::vector<T> makeSinusVector(const std::vector<double> &time, double f) {
    std::vector<T> sinus(time.size());
    std::transform(time.begin(), time.end(), sinus.begin(),
                   [&f](double d) { return std::sin(2 * std::numbers::pi * f * d); });
    return sinus;
}

template<typename T>
std::vector<T> makeAMSinusVector(const std::vector<double> &time, double fp, double fm) {
    std::vector<T> sinus(time.size());
    std::transform(time.begin(), time.end(), sinus.begin(),
                   [&](double d) {
                       return (1 + std::sin(2 * std::numbers::pi * fm * d))
                              * std::sin(2 * std::numbers::pi * fp * d);
                   });
    return sinus;
}


std::vector<double> psd(const std::vector<Complex> &dft) {
    std::vector<double> p(dft.size());
    for (std::size_t k = 0; k < p.size(); k++)
        p[k] = (dft[k] * std::conj(dft[k])).real();
    return p;
}


std::vector<double> toReal(const std::vector<Complex> &x) {
    std::vector<double> r(x.size());
    std::transform(x.begin(), x.end(), r.begin(), [](Complex c) { return c.real(); });
    return r;
}

template<typename Tcontainer, typename Tsignal>
const std::vector<Tcontainer> generate_random_vector(Tsignal inf, Tsignal sup, std::size_t size) {
    std::vector<Tcontainer> v(size);
    std::random_device seeder;
    std::mt19937 random_generator(seeder()); //Standard mersenne_twister_engine seeded with rd()
    if constexpr (std::is_same_v<Tsignal, int>) {
        std::uniform_int_distribution<> uniformIntDistribution(inf, sup);
        std::generate(v.begin(), v.end(), [&]() { return uniformIntDistribution(random_generator); });
    }
    if constexpr (std::is_same_v<Tsignal, double>) {
        std::uniform_real_distribution<> uniformRealDistribution(inf, sup);
        std::generate(v.begin(), v.end(), [&]() { return uniformRealDistribution(random_generator); });
    }
    return v;
}


template<typename Duration = std::chrono::microseconds,
        typename F,
        typename ... Args>
typename Duration::rep wall_time_profile(F &&fun, Args &&... args) {
    const auto beg = std::chrono::high_resolution_clock::now();
    std::forward<F>(fun)(std::forward<Args>(args)...);
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<Duration>(end - beg).count();
}

template<typename Duration = std::chrono::microseconds,
        typename F,
        typename ... Args>
typename Duration::rep cpu_time_profile(F &&fun, Args &&... args) {
    struct timespec begin, end;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
    std::forward<F>(fun)(std::forward<Args>(args)...);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    return end.tv_nsec - begin.tv_nsec;
}

std::pair<typename std::chrono::milliseconds::rep, typename std::chrono::milliseconds::rep>
average_stddev(const std::vector<typename std::chrono::milliseconds::rep> &data) {
    double mean = std::reduce(data.cbegin(), data.cend(), 0.0) / data.size();
    double sqSum = 0.0;
    std::for_each(data.cbegin(), data.cend(),
                  [&](const typename std::chrono::milliseconds::rep d) {
                      sqSum += (d - mean) * (d - mean);
                  });
    return std::make_pair(mean, std::sqrt(sqSum / (data.size() - 1)));
}

template<typename Duration = std::chrono::microseconds,
        typename F,
        typename ... Args>
typename Duration::rep wall_time_average_profile(std::size_t nRuns, F &&fun, Args &&... args) {
    std::vector<typename std::chrono::microseconds::rep> samples(nRuns);
    for (auto &sample : samples) {
        const auto beg = std::chrono::high_resolution_clock::now();
        std::forward<F>(fun)(std::forward<Args>(args)...);
        const auto end = std::chrono::high_resolution_clock::now();
        sample = std::chrono::duration_cast<Duration>(end - beg).count();
    }
    auto[mean, stddev] = average_stddev(samples);
    std::cout << nRuns << " runs: average = " << mean << " µs, stdev = " << stddev << " µs." << std::endl;
    return mean;
}


template<typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &s, const std::array<T, SIZE> &a) {
    s << '[';
    if (!a.empty()) {
        std::copy(a.cbegin(), a.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << a.back();
    }
    return s << ']';
}


template<typename T>
std::tuple<bool, int, double> epsilon_vector_compare(std::string title, std::vector<T> x, std::vector<T> y) {

    if (x.size() != y.size())
        throw std::invalid_argument("Size's vectors must be equal !");

    bool same{false};
    if (x == y)
        same = true;

    int count = 0;
    double max_delta = 0.0;
    for (std::size_t k = 0; k < x.size(); k++) {
        if (abs(x[k]) - abs(y[k]) > std::numeric_limits<double>::epsilon())
            count++;
        if (abs(x[k] - y[k]) > max_delta)
            max_delta = abs(x[k] - y[k]);
    }
    std::cout << std::boolalpha << title
              << " are same ? --> " << same
              << "\t distinct = " << count
              << "\t   max delta = " << max_delta << std::endl;
    return std::make_tuple(same, count, max_delta);
}

template<typename F,
        typename ... Args>
void peakDetection(std::string title, double Fs, std::vector<Complex> &signal, F &&fun, Args &&... args) {
    std::forward<F>(fun)(std::forward<Args>(args)...);
    auto freq = makeFrequencyVector(Fs, N);
    auto periodogram = psd(signal);
    auto max_elem = std::max_element(periodogram.cbegin(), periodogram.cend() - N / 2);
    auto max_index = std::distance(periodogram.cbegin(), max_elem);
    std::cout << title << " ----- "
              << "Fs : " << Fs << " Hz,  Resolution : " << Fs / N
              << "\t Max index --> "
              << max_index
              << "\t Max frequency --> "
              << Fs * max_index / (1.0 * N)
              << " Hz,  Max Value : " << periodogram.at(max_index)
              << std::endl;
}

void windowing(const std::array<double, N> &w, std::vector<Complex> &s) {
    std::transform(s.begin(),
                   s.end(),
                   s.begin(),
                   [&, index = -1](Complex c)mutable {
                       index++;
                       return w[index] * c;
                   });
}

#endif