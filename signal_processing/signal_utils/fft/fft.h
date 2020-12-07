//
// Created by salyd on 04/12/2020.
//

#ifndef SIGNAL_PROCESSING_FFT_H
#define SIGNAL_PROCESSING_FFT_H

#include <vector>
#include <numbers>
#include <array>
#include <iostream>
#include "../common.h"

void v_rect_dit_fft(std::vector<Complex> &x);

void v_rect_dit_fft_array(Complex *x, std::size_t x_size);

void ite_dit_fft(std::vector<Complex> &x);

void ite_dit_fft_array(Complex *x, std::size_t x_size);

void v_rect_dif_fft(std::vector<Complex> &x);

void v_rect_dif_fft_array(Complex *x, std::size_t x_size);

void ite_dif_fft(std::vector<Complex> &x);

void ite_dif_fft_array(Complex *x, size_t x_size);


#endif //SIGNAL_PROCESSING_FFT_H
