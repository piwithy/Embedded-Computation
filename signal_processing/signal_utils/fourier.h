//
// Created by jezegoup on 23/11/2020.
//

#ifndef SIGNAL_PROCESSING_FOURIER_H
#define SIGNAL_PROCESSING_FOURIER_H

#ifndef SIGNAL_PROCESSING_COMMON_H

#include "common.h"

#endif

#include <vector>
#include <numbers>
#include <array>
using namespace std::complex_literals;

template<typename T>
std::vector<Complex> naive_dft(const std::vector<T> &X);

template<typename T>
std::vector<Complex> almost_naive_dft(const std::vector<T> &X);

template<typename T>
std::vector<Complex> dft(const std::vector<T> &X);

#include "fourier.tpp"


#endif //SIGNAL_PROCESSING_FOURIER_H
