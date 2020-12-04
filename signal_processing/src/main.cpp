//
// Created by jezegoup on 23/11/2020.
//
#include <iostream>
#include "src/SignalProcessingConfig.h"
#include "signal_utils.h"
#include "fourier.h"

void test_dft() {
    /*double f= 889.0;
    auto time = makeTimeVector(Fs, N);
    auto dft_sinus = makeSinusVector<double>(time, f);
    auto X = dft(dft_sinus);
    std::cout << "DTF ----- " ;
    auto data = generate_random_vector<Complex, double>(-0.5, 0.5, N);
    wall_time_average_profile(100, dft<Complex>, data);*/
    double f = 889.0;
    double Fs = 22050.;
    auto time = makeTimeVector(Fs, N);
    auto dft_sinus = makeSinusVector<double>(time, f);
    //auto X = dft(dft_sinus);
    auto lut = make_nroot_lut<N>();
    auto X = lut_dft<N>(dft_sinus, lut);
//std::cout << X << std::endl;
    auto periodogram = psd(X);
    auto max_elem = std::max_element(periodogram.cbegin(), periodogram.cend() - N / 2);
    auto max_index = std::distance(periodogram.cbegin(), max_elem);
    std::cout << " ----- "
              << "Fs : " << Fs << " Hz,  Resolution : " << Fs / N
              << "\t Max index --> "
              << max_index
              << "\t Max frequency --> "
              << Fs * max_index / (1.0 * N)
              << " Hz,  Max Value : " << periodogram.at(max_index)
              << std::endl;
    std::cout << "DTF ----- ";
    auto data = generate_random_vector<Complex, double>(-0.5, 0.5, N);
    wall_time_average_profile(100, naive_dft<Complex>, data);
    std::cout << "LUT DTF ----- ";
    wall_time_average_profile(100, lut_dft<N, Complex>, data, lut);
}


int main() {
    std::cout << "Version " << SIGNAL_PROCESSING_VERSION_MAJOR << "."
              << SIGNAL_PROCESSING_VERSION_MINOR << std::endl;
    std::cout << "Testing DFT!" << std::endl;
    /*auto w = make_lut<N>();
    std::cout << w << std::endl;*/
    test_dft();
    return 0;
}
