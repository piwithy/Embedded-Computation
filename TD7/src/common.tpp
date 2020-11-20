#ifndef FT_GLOBAL_TPP
#define FT_GLOBAL_TPP

#include <random>

template<typename T>
std::ostream &operator<<(std::ostream &s, std::vector<T> &v) {
    s << '[';
    if (!v.empty()) {
        std::copy(v.cbegin(), v.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << v.back();
    }
    return s << ']';
}

template<typename T>
std::vector<T> makeSinusVector(const std::vector<double> &time, double f) {
    std::vector<T> sin_vector(time.size());
    std::transform(time.cbegin(),
                   time.cend(),
                   sin_vector.begin(),
                   [f](double t) { return sin(f, t); });
    sin_vector.shrink_to_fit();
    return sin_vector;
}

template<typename T>
std::vector<T> makeAMSinusVector(const std::vector<double> &time, double fp, double fm) {
    std::vector<T> am_sin_vector(time.size());
    std::transform(time.cbegin(),
                   time.cend(),
                   am_sin_vector.begin(),
                   [fp, fm](double t) { return sin(fm, t) * sin(fp, t); });
    am_sin_vector.shrink_to_fit();
    return am_sin_vector;
}

template<typename T>
std::vector<T> generate_random_vector(double inf, double sup, std::size_t size) {
    std::random_device seeder;
    std::mt19937 random_generator(seeder());
    std::uniform_real_distribution<> uniformDistribution(inf, sup);
    std::vector<T> random_vector(size);
    std::generate(random_vector.begin(), random_vector.end(), [&]() { return uniformDistribution(random_generator); });
    random_vector.shrink_to_fit();
    return random_vector;
}

#endif //FT_GLOBAL_TPP