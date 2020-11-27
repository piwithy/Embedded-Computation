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

template<typename T>
std::vector<Complex> almost_naive_dft(const std::vector<T> &X) {
    auto x_size = X.size();
    std::vector<Complex> x(x_size);
    T init = 0.;
    for (auto k = 0; k < X.size() - 1; k++) {
        x.at(k) = std::transform_reduce(std::execution::par, X.cbegin(), X.cend() - 1, init, std::plus<T>(),
                                        [&x_size, &k, n = 0](T s_n) mutable {
                                            return s_n * std::exp(((-2. * 1i * std::numbers::pi * (double) (k * n++))) / ((double) x_size));
                                        });
    }
    return x;
}

template<typename T>
std::vector<Complex> dft(const std::vector<T> &X) {
    auto x_size = X.size();
    std::vector<Complex> x(x_size);
    T init = 0.;
    std::transform(std::execution::par, X.begin(), X.cend() - 1, x.begin(), [&, k = 0](T s_k) mutable {
        auto kapt = k++;
        return std::transform_reduce(std::execution::par, X.cbegin(), X.cend() - 1, init, std::plus<T>(),
                                     [&x_size, &kapt, n = 0](T s_n) mutable {
                                         return s_n * std::exp(((-2. * 1i * std::numbers::pi * (double) (kapt * n++))) / ((double) x_size));
                                     });
    });
    return x;
}