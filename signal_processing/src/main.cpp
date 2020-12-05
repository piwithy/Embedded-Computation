//
// Created by jezegoup on 23/11/2020.
//
#include <iostream>
#include "src/SignalProcessingConfig.h"
#include "signal_utils.h"
#include "dft.h"
#include "fft.h"

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

void test_fft() {
    double f = 889.0;
    double Fs = 22050.;
    auto time = makeTimeVector(Fs, N);
    auto dft_sinus = makeSinusVector<Complex>(time, f);
    //auto X = dft(dft_sinus);
    v_rect_dit_fft_array(dft_sinus.data(), dft_sinus.size());
//std::cout << X << std::endl;
    auto periodogram = psd(dft_sinus);
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
    std::cout << "FFT ----- ";
    auto data = generate_random_vector<Complex, double>(-0.5, 0.5, N);
    wall_time_average_profile(100, v_rect_dit_fft, data);
    std::cout << "ARRAY FFT ----- ";
    wall_time_average_profile(100, v_rect_dit_fft_array, data.data(), data.size());
}


int main() {
    std::cout << "Version " << SIGNAL_PROCESSING_VERSION_MAJOR << "."
              << SIGNAL_PROCESSING_VERSION_MINOR << std::endl;
    //std::cout << "Testing DFT!" << std::endl;
    //test_dft();
    std::cout << "Testing FFT!" << std::endl;
    test_fft();
    return 0;
}
