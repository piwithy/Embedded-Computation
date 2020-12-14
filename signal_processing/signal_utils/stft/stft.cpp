//
// Created by salyd on 07/12/2020.
//

#include "stft.h"
#include "../fft/fft.h"
#include "../signal_utils.h"

#include <execution>

std::tuple<std::vector<std::vector<Complex>>, std::vector<double>, std::vector<double>>
process_signal(const std::vector<float> &x) {
    std::vector<std::vector<Complex>> bins;
    std::vector<double> average;
    std::vector<double> std_dev;
    std::size_t nBins = (x.size() / N);
    auto window = hamming_window();
    for (std::size_t bin_idx = 0; bin_idx < nBins; bin_idx++) {

        std::vector<Complex> even_bin(N), odd_bin(N);
        auto even_start = x.cbegin() + bin_idx * N;
        auto odd_start = x.cbegin() + (bin_idx * N) + (N / 2);
        std::copy(even_start, even_start + N, even_bin.begin());
        std::copy(odd_start, odd_start + N, odd_bin.begin());

        windowing(window, even_bin);
        windowing(window, odd_bin);
        ite_dit_fft(even_bin);
        ite_dit_fft(odd_bin);

        std::tuple<double, double> bin_avg_stddev_even = compute_avg_stddev(even_bin);
        std::tuple<double, double> bin_avg_stddev_odd = compute_avg_stddev(odd_bin);

        average.push_back(std::get<0>(bin_avg_stddev_even));
        std_dev.push_back(std::get<1>(bin_avg_stddev_even));

        average.push_back(std::get<0>(bin_avg_stddev_odd));
        std_dev.push_back(std::get<1>(bin_avg_stddev_odd));

        bins.push_back(even_bin);
        bins.push_back(odd_bin);
    }

    bins.shrink_to_fit();
    return std::make_tuple(bins, average, std_dev);
}

std::tuple<double, double> compute_avg_stddev(const std::vector<Complex> &x) {
    double avg = std::reduce(std::execution::par, x.cbegin(), x.cend()).real() / x.size();
    double stddev = std::sqrt( std::transform_reduce(
            std::execution::par,
            x.cbegin(),
            x.cend(),
            0.,
            std::plus(),
            [avg](Complex x) {
                double x_r = x.real();
                return ((x_r - avg) * (x_r - avg));
            }) / (double) (x.size() - 1));
    return std::make_tuple(avg, stddev);
}


std::tuple<std::vector<double>, std::vector<double>> compute_avg_stddev(const std::vector<std::vector<Complex>> &bins) {
    std::vector<double> average;
    std::vector<double> standard_dev;
    for (auto &bin:bins) {
        double avg = (std::reduce(bin.cbegin(), bin.cend())).real() / (float) bin.size();
        double std_dev = std::sqrt(std::transform_reduce(
                bin.cbegin(),
                bin.cend(),
                0.,
                std::plus(),
                [avg](Complex x) {
                    double x_r = x.real();
                    return std::pow((x_r - avg), 2);
                }) / (double) (bin.size() - 1));
        average.push_back(avg);
        standard_dev.push_back(std_dev);
    }
    average.shrink_to_fit();
    standard_dev.shrink_to_fit();

    return std::make_tuple(average, standard_dev);
}
