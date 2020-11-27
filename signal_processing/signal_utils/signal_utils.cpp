//
// Created by jezegoup on 23/11/2020.
//

#include "signal_utils.h"
#include <iostream>


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

std::pair<typename std::chrono::milliseconds::rep, typename std::chrono::milliseconds::rep>
average_stddev(const std::vector<typename std::chrono::milliseconds::rep> &data) {
    double mean = std::reduce(data.cbegin(), data.cend(), 0.0) / data.size();
    double sqSum = 0.0;
    std::for_each(data.cbegin(), data.cend(),
                  [&](const typename std::chrono::milliseconds::rep d) {
                      sqSum += (d - mean) * (d - mean);
                  });
    return std::make_pair(mean, std::sqrt(sqSum / ((double) data.size() - 1)));
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
