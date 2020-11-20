#include "common.h"
#include <iostream>

int main(int argc, char *argv[]) {
    std::vector<double> test_vec{-0.236468, -0.192966, -0.193747, 0.12682};
    std::cout << "Test Vector: " << test_vec << std::endl;
    auto test_time = makeTimeVector(10, 100);
    std::cout << "Test Time: " << test_time << std::endl;
    auto test_freq = makeFrequencyVector(10, 100);
    std::cout << "Test Frequency: " << test_freq << std::endl;
    std::vector<Complex> comp_vec{Complex(0, 0), Complex(0, 1), Complex(1, 1), Complex(1, 0)};
    std::cout << "Complex Vector: " << comp_vec << std::endl;
    auto real_part = toReal(comp_vec);
    std::cout << "Re(Complex Vector): " << real_part << std::endl;
    auto imaginary_part = toImag(comp_vec);
    std::cout << "Im(Complex Vector): " << imaginary_part << std::endl;
    auto cplx_form_real = toComplex(real_part);
    std::cout << "Complex From Real: " << cplx_form_real << std::endl;
    std::vector<double> sin_vector = makeSinusVector<double>(test_time, 10);
    std::cout << "Sin Vector: " << sin_vector << std::endl;
    auto random_vec = generate_random_vector<double>(0., 10., 5);
    std::cout << "Random Vector: " << random_vec << std::endl;
    return 0;
}