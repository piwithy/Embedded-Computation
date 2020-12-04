#include <vector>
#include <numbers>
#include <execution>
#include <numeric>

template<typename T>
std::vector<Complex> naive_dft(const std::vector<T> &X) {
    auto x_size = X.size();
    std::vector<Complex> x(x_size);
    for (auto k = 0; k < x_size - 1; k++) {
        for (auto n = 0; n < x_size - 1; n++) {
            x.at(k) = x.at(k) +
                      X.at(n) * std::exp(((-2. * 1i * std::numbers::pi * (double) (k * n))) / ((double) x_size));
        }
    }
    return x;
}

template<size_t DIM, typename T>
std::vector<Complex> lut_dft(const std::vector<T> &X, std::array<Complex, DIM * DIM> &lut) {
    auto x_size = X.size();
    std::vector<Complex> x(x_size);
    for (auto k = 0; k < x_size - 1; k++) {
        for (auto n = 0; n < x_size - 1; n++) {
            x.at(k) = x.at(k) + X.at(n) * lut[n + k * DIM];
        }
    }
    return x;
}

template<std::size_t DIM>
constexpr std::array<Complex, DIM * DIM> make_nroot_lut() {
    std::array<Complex, DIM * DIM> w;
    for (auto k = 0; k < DIM; k++) {
        for (auto n = 0; n < DIM; n++) {
            double arg = (-2. * std::numbers::pi * (double) (k * n)) / ((double) DIM);
            w[n + k * DIM] = Complex(std::cos(arg), std::sin(arg));
        }
    }
    return w;
}

template<typename T>
std::vector<Complex> recursive_fft(const std::vector<T> &X) {
    auto x_size = X.size();
    std::vector<Complex> v;
    std::vector<T> even(x_size / 2);
    std::vector<T> odd(x_size / 2);
    std::copy_if(std::execution::par, X.cbegin(), X.cend(), even.begin(),
                 [n = 0](T x) mutable { return n++ % 2 == 0; });
    std::copy_if(std::execution::par, X.cbegin(), X.cend(), odd.begin(),
                 [n = 0](T x) mutable { return n++ % 2 != 0; });
    auto odd_comp = recursive_fft(odd);
    auto even_comp = recursive_fft(even);

    for(auto k=0; k<(x_size/2) - 1; k++){

    }

    return v;
}