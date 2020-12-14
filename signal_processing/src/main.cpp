//
// Created by jezegoup on 23/11/2020.
//
#include <iostream>
#include "src/SignalProcessingConfig.h"
#include "signal_utils.h"
#include "dft/dft.h"
#include "fft/fft.h"
#include "AuAudioFile.h"

/*void test_dft() {
    /*double f= 889.0;
    auto time = makeTimeVector(Fs, N);
    auto dft_sinus = makeSinusVector<double>(time, f);
    auto X = dft(dft_sinus);
    std::cout << "DTF ----- " ;
    auto data = generate_random_vector<Complex, double>(-0.5, 0.5, N);
    wall_time_average_profile(100, dft<Complex>, data);*//*
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
}*/

template<typename T>
void periodogram(const std::string &title, const std::vector<T> &x, double Fs) {
    auto periodogram = psd(x);
    auto max_elem = std::max_element(periodogram.cbegin(), periodogram.cend() - N / 2);
    auto max_index = std::distance(periodogram.cbegin(), max_elem);
    std::cout << title << " ----- "
              << "Fs : " << Fs << " Hz,  Resolution : " << Fs / N
              << "\t Max index --> "
              << max_index
              << "\t Max frequency --> "
              << Fs * max_index / (1.0 * N)
              << " Hz,  Max Value : " << periodogram.at(max_index)
              << " ----- " << std::endl;
}

void test_fft() {
    double f = 889.0;
    double Fs = 22050.;
    auto time = makeTimeVector(Fs, N);
    auto sin_vector_dit_fft_recur = makeSinusVector<Complex>(time, f);
    auto sin_vector_dit_fft_recur_arr = makeSinusVector<Complex>(time, f);
    auto sin_vector_dit_fft_iter = makeSinusVector<Complex>(time, f);
    auto sin_vector_dit_fft_iter_arr = makeSinusVector<Complex>(time, f);
    auto sin_vector_dif_fft_recur = makeSinusVector<Complex>(time, f);
    auto sin_vector_dif_fft_recur_arr = makeSinusVector<Complex>(time, f);
    auto sin_vector_dif_fft_iter = makeSinusVector<Complex>(time, f);
    auto sin_vector_dif_fft_iter_arr = makeSinusVector<Complex>(time, f);

    //computing ffts
    v_rect_dit_fft(sin_vector_dit_fft_recur);
    v_rect_dit_fft_array(sin_vector_dit_fft_recur_arr.data(), sin_vector_dit_fft_recur_arr.size());
    ite_dit_fft(sin_vector_dit_fft_iter);
    ite_dit_fft_array(sin_vector_dit_fft_iter_arr.data(), sin_vector_dit_fft_iter_arr.size());
    v_rect_dif_fft(sin_vector_dif_fft_recur);
    v_rect_dif_fft_array(sin_vector_dif_fft_recur_arr.data(), sin_vector_dif_fft_recur_arr.size());
    ite_dif_fft(sin_vector_dif_fft_iter);
    ite_dif_fft_array(sin_vector_dif_fft_iter_arr.data(), sin_vector_dif_fft_iter_arr.size());

    std::cout << " ----- FFT COMPUTING | SINUS: f=889Hz sampled at 22050Hz -----" << std::endl;

    periodogram("DIT RECUR FFT VEC", sin_vector_dit_fft_recur, Fs);
    periodogram("DIT RECUR FFT ARR", sin_vector_dit_fft_recur_arr, Fs);

    periodogram("DIT ITER  FFT VEC", sin_vector_dit_fft_iter, Fs);
    periodogram("DIT ITER  FFT ARR", sin_vector_dit_fft_iter_arr, Fs);

    std::cout << std::endl;

    periodogram("DIF RECUR FFT VEC", sin_vector_dif_fft_recur, Fs);
    periodogram("DIF RECUR FFT ARR", sin_vector_dif_fft_recur_arr, Fs);

    periodogram("DIF ITER  FFT VEC", sin_vector_dif_fft_iter, Fs);
    periodogram("DIF ITER  FFT ARR", sin_vector_dif_fft_iter_arr, Fs);

    std::cout << " ----- FFT SPEED TEST | RANDOM VECTOR size N=" << N << " -----" << std::endl;


    auto data = generate_random_vector<Complex, double>(-0.5, 0.5, N);
    std::cout << "DIT RECUR FFT VEC ----- ";
    wall_time_average_profile(100, v_rect_dit_fft, data);
    std::cout << "DIT RECUR FFT ARR ----- ";
    wall_time_average_profile(100, v_rect_dit_fft_array, data.data(), data.size());
    std::cout << "DIT ITER  FFT VEC ----- ";
    wall_time_average_profile(100, ite_dit_fft, data);
    std::cout << "DIT ITER  FFT ARR ----- ";
    wall_time_average_profile(100, ite_dit_fft_array, data.data(), data.size());
    std::cout << std::endl;
    std::cout << "DIF RECUR FFT VEC ----- ";
    wall_time_average_profile(100, v_rect_dif_fft, data);
    std::cout << "DIF RECUR FFT ARR ----- ";
    wall_time_average_profile(100, v_rect_dif_fft_array, data.data(), data.size());
    std::cout << "DIF ITER  FFT VEC ----- ";
    wall_time_average_profile(100, ite_dif_fft, data);
    std::cout << "DIF ITER  FFT ARR -----";
    wall_time_average_profile(100, ite_dif_fft_array, data.data(), data.size());

    epsilon_vector_compare("DIF ITER Vector, Array", sin_vector_dif_fft_iter, sin_vector_dif_fft_iter_arr);
}

void audio_test() {
    auto disco = AuAudioFile("../../assets/disco.00050.au", true);
}


int main() {
    std::cout << "Version " << SIGNAL_PROCESSING_VERSION_MAJOR << "."
              << SIGNAL_PROCESSING_VERSION_MINOR << std::endl;
    /*std::cout << "Testing DFT!" << std::endl;
    test_dft();*/
    std::cout << "Testing FFT!" << std::endl;
    test_fft();
    std::cout << "Testing AUDIO!" << std::endl;
    audio_test();
    return 0;
}
