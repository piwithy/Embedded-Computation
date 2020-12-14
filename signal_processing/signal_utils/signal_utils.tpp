
#include <iostream>
#include <iterator>
#include <numbers>
#include <random>
#include <tuple>

template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
    s << '[';
    if (!v.empty()) {
        std::copy(v.cbegin(), v.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << v.back();
    }
    return s << ']';
}

template<typename T>
std::vector<T> makeSinusVector(const std::vector<double> &time, double f) {
    std::vector<T> sinus(time.size());
    std::transform(time.begin(), time.end(), sinus.begin(),
                   [&f](double d) { return std::sin(2 * std::numbers::pi * f * d); });
    return sinus;
}

template<typename T>
std::vector<T> makeAMSinusVector(const std::vector<double> &time, double fp, double fm) {
    std::vector<T> sinus(time.size());
    std::transform(time.begin(), time.end(), sinus.begin(),
                   [&](double d) {
                       return (1 + std::sin(2 * std::numbers::pi * fm * d))
                              * std::sin(2 * std::numbers::pi * fp * d);
                   });
    return sinus;
}

template<typename Tcontainer, typename Tsignal>
std::vector<Tcontainer> generate_random_vector(Tsignal inf, Tsignal sup, std::size_t size) {
    std::vector<Tcontainer> v(size);
    std::random_device seeder;
    std::mt19937 random_generator(seeder()); //Standard mersenne_twister_engine seeded with rd()
    if constexpr (std::is_same_v<Tsignal, int>) {
        std::uniform_int_distribution<> uniformIntDistribution(inf, sup);
        std::generate(v.begin(), v.end(), [&]() { return uniformIntDistribution(random_generator); });
    }
    if constexpr (std::is_same_v<Tsignal, double>) {
        std::uniform_real_distribution<> uniformRealDistribution(inf, sup);
        std::generate(v.begin(), v.end(), [&]() { return uniformRealDistribution(random_generator); });
    }
    return v;
}

template<typename F,
        typename ... Args>
Duration::rep wall_time_profile(F &&fun, Args &&... args) {
    const auto beg = std::chrono::high_resolution_clock::now();
    std::forward<F>(fun)(std::forward<Args>(args)...);
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<Duration>(end - beg).count();
}

template<typename F,
        typename ... Args>
Duration::rep cpu_time_profile(F &&fun, Args &&... args) {
    struct timespec begin{}, end{};
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &begin);
    std::forward<F>(fun)(std::forward<Args>(args)...);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    return end.tv_nsec - begin.tv_nsec;
}

template<typename F,
        typename ... Args>
Duration::rep wall_time_average_profile(std::size_t nRuns, F &&fun, Args &&... args) {
    std::vector<typename std::chrono::microseconds::rep> samples(nRuns);
    for (auto &sample : samples) {
        const auto beg = std::chrono::high_resolution_clock::now();
        std::forward<F>(fun)(std::forward<Args>(args)...);
        const auto end = std::chrono::high_resolution_clock::now();
        sample = std::chrono::duration_cast<Duration>(end - beg).count();
    }
    auto[mean, stddev] = average_stddev(samples);
    std::cout << nRuns << " runs: average = " << (double) mean << " µs, stdev = " << stddev << " µs."
              << std::endl;
    return mean;
}


template<typename T, size_t SIZE>
std::ostream &operator<<(std::ostream &s, const std::array<T, SIZE> &a) {
    s << '[';
    if (!a.empty()) {
        std::copy(a.cbegin(), a.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << a.back();
    }
    return s << ']';
}

template<typename T>
std::tuple<bool, int, double> epsilon_vector_compare(const std::string &title, std::vector<T> x, std::vector<T> y) {

    if (x.size() != y.size())
        throw std::invalid_argument("Size's vectors must be equal !");

    bool same{false};
    if (x == y)
        same = true;

    int count = 0;
    double max_delta = 0.0;
    for (std::size_t k = 0; k < x.size(); k++) {
        if (abs(abs(x[k]) - abs(y[k])) > std::numeric_limits<double>::epsilon())
            count++;
        if (abs(x[k]) - abs(y[k]) > max_delta)
            max_delta = abs(abs(x[k]) - abs(y[k]));
    }
    std::cout << std::boolalpha << title
              << " are same ? --> " << same
              << "\t distinct = " << count
              << "\t accuracy = " << std::round((((double) (x.size() - count) / x.size()) * 100000) / 1000) << "%"
              << "\t max delta = " << max_delta << std::endl;
    return std::make_tuple(same, count, max_delta);
}

template<typename F,
        typename ... Args>
void peakDetection(const std::string &title, double Fs, std::vector<Complex> &signal, F &&fun, Args &&... args) {
    std::forward<F>(fun)(std::forward<Args>(args)...);
    auto freq = makeFrequencyVector(Fs, N);
    auto periodogram = psd(signal);
    auto max_elem = std::max_element(periodogram.cbegin(), periodogram.cend() - N / 2);
    auto max_index = std::distance(periodogram.cbegin(), max_elem);
    std::cout << title << " ----- "
              << "Fs : " << Fs << " Hz,  Resolution : " << Fs / N
              << "\t Max index --> "
              << max_index
              << "\t Max frequency --> "
              << Fs * max_index / (1.0 * N)
              << " Hz,  Max Value : " << periodogram.at(max_index)
              << std::endl;
}


constexpr std::array<double, N> cosine_window(double a0) {
    std::array<double, N> cosine{};
    int N_item = cosine.size();
    std::generate(cosine.begin(),
                  cosine.end(),
                  [N_item, a0, n = 0]() mutable {
                      double Re;
                      Re = a0 * (1 - std::cos((2 * std::numbers::pi * n++) / N_item));
                      return Re;
                  });
    return cosine;
}

constexpr std::array<double, N> hann_window() {
    return cosine_window(0.5);
}

constexpr std::array<double, N> hamming_window() {
    std::array<double, N> w{};
    std::generate(w.begin(), w.end(),
                  [&, index = -1]()mutable {
                      index++;
                      return (0.54 - 2 * 0.23 * std::cos(2 * std::numbers::pi * index / N));
                  });
    return w;
    //return cosine_window(25. / 64.);
}

constexpr std::array<double, N> blackman_window() {
    double alpha = 0.16, a0 = (1 - alpha) / 2, a1 = 0.5, a2 = alpha / 2;
    std::array<double, N> blackman{};
    int N_item = blackman.size();
    std::generate(blackman.begin(),
                  blackman.end(),
                  [a0, a1, a2, N_item, n = 0]() {
                      double Re;
                      Re = a0 - a1 * std::cos((2 * std::numbers::pi * n) / N_item) +
                           a2 * std::cos((4 * std::numbers::pi * n) / N_item);
                      return Re;
                  });
    return blackman;
}