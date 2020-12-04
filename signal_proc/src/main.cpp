//
// Created by jezegoup on 23/11/2020.
//

#include "global.h"
#include "signalutils.h"
#include "dft.h"

void test_dft() {
    double f = 889.0;
    double Fs = 22050.0;
    auto time = makeTimeVector(Fs, N);
    auto dft_sinus = makeSinusVector<double>(time, f);
    auto X = naive_dft(dft_sinus);
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
}

int main() {
    std::cout << "Testing DFT !" << std::endl;
    test_dft();
    return 0;
}

