#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <random>
#include <execution>

template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
    s << '[';
    if (!v.empty()) {
        std::copy(v.cbegin(), v.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << v.back();
    }
    return s << ']';
}


void foreachLambdaParameters() {
    std::vector<int> v(3, -3);
    for_each(v.cbegin(), v.cend(), [](int value) { std::cout << value << ", "; });
    std::cout << std::endl;
    for_each(v.begin(), v.end(), [](int &value) { std::cout << ++value << ", "; });
    std::cout << std::endl;
    for_each(v.begin(), v.end(), [](auto value) { std::cout << ++value << ", "; });
    std::cout << std::endl;
    for (auto val: v)
        std::cout << val << std::endl;
}

template<typename T>
void print_vector(std::vector<T> v) {
    std::cout << "v: " << v << std::endl;
}

void maredduce() {
    std::vector<int> v(1024);
    std::random_device seeder;
    std::mt19937 random_generator(seeder());
    std::uniform_int_distribution<> uniformIntDistribution(1, 65535);
    std::generate(v.begin(), v.end(), [&]() { return uniformIntDistribution(random_generator); });
    print_vector(v);
    std::cout << "min: " << *std::min_element(v.cbegin(), v.cend()) << " max: "
              << *std::max_element(v.cbegin(), v.cend()) << std::endl;
    std::transform(std::execution::par, v.begin(), v.end(), v.begin(), [](int i) { return (i > 32767) ? 32767 : i; });
    print_vector(v);
    std::cout << "min: " << *std::min_element(v.cbegin(), v.cend()) << " max: "
              << *std::max_element(v.cbegin(), v.cend()) << std::endl;
    const int result = std::reduce(std::execution::par, v.cbegin(), v.cend());
    std::cout << "sum(v)=" << result << std::endl;
    auto result2 = std::transform_reduce(v.cbegin(), v.cend(), 1, [](int a, int b) { return a * b; },
                                         [](int i) { return (i > 64) ? 64 : i; });
    auto moy = std::reduce(v.cbegin(), v.cend()) / v.size();
    std::cout << "moy=" << moy << std::endl;
}

template<typename T>
double average(std::vector<T> vec) {
    return std::reduce(std::execution::par, vec.cbegin(), vec.cend()) / vec.size();
}

template<typename T>
double standard_deviation(std::vector<T> v, double avg) {
    return std::sqrt(std::transform_reduce(
            std::execution::par,
            v.cbegin(),
            v.cend(),
            0.,
            std::plus(),
            [avg](double x) { return std::pow((x - avg), 2); }
    ) / (v.size() - 1));
}

template<typename T>
double standard_deviation(std::vector<T> v) {
    return standard_deviation(v, average(v));
}

void calcul() {
    std::random_device seeder;
    std::mt19937 random_generator(seeder());
    double inf = 0.0;
    double sup = 100.0;
    std::uniform_real_distribution<> uniformDistribution(inf, sup);
    std::vector<double> v(1u << 24u);
    std::generate(v.begin(), v.end(), [&]() { return uniformDistribution(random_generator); });
    auto vec_sum = std::reduce(std::execution::par, v.cbegin(), v.cend());
    std::vector<double> v_ec(v.size());
    std::cout << "vec_sum: " << vec_sum << std::endl;
    std::transform(v.cbegin(), v.cend(), v_ec.begin(), [](double d) { return d > 50. ? 50. : d; });
    std::cout << "v_ec max: " << *std::max_element(v_ec.cbegin(), v_ec.cend()) << std::endl;
    auto v_p = std::make_pair(average(v), standard_deviation(v));
    std::cout << "calcul\tm= " << v_p.first << "\tstd= " << v_p.second << std::endl;
    std::cout << "theorie\tm= "<< (inf+sup)/2 << "\t\tstd= " << (sup-inf)/std::sqrt(12) << std::endl ;
}

int main() {
    /*foreachLambdaParameters();
    std::vector<int> v(1024, 0);
    std::cout << "v: " << v << std::endl;
    std::fill(v.begin(), v.end(), -1);
    std::cout << "v: " << v << std::endl;
    std::iota(v.begin(), v.end(), 21);
    print_vector(v);
    std::generate(v.begin(), v.end(), [n = 10]() mutable { return 2 * n++ + 1; });
    print_vector(v);
    std::random_device seeder;
    std::mt19937 random_generator(seeder());
    std::uniform_int_distribution<> uniformIntDistribution(0, 65535);
    std::generate(v.begin(), v.end(), [&]() { return uniformIntDistribution(random_generator); });
    print_vector(v);

    std::vector<int> vp(10);
    std::iota(vp.begin(), vp.end(), 1);
    std::vector<int> u(10);
    auto itu = u.begin();
    std::cout << "u: " << u << std::endl;
    std::copy(vp.cbegin(), vp.cend(), itu);
    std::cout << "vp: " << vp << std::endl;
    std::cout << "u: " << u << std::endl;
    u.clear();
    std::cout << "u: " << u << std::endl;
    std::copy(vp.cbegin(), vp.cend(), std::back_inserter(u));
    std::cout << "vp: " << vp << std::endl;
    std::cout << "u: " << u << std::endl;
    u.clear();
    std::copy(vp.cbegin(), vp.cend(), std::ostream_iterator<int>(std::cout));
    std::cout << std::endl;
    u.clear();
    std::copy_if(vp.cbegin(), vp.cend(), std::back_insert_iterator(u), [](int x) { return (x % 2) == 0; });
    std::cout << "u: " << u << std::endl;
    u.clear();
    std::remove_copy_if(vp.cbegin(), vp.cend(), std::back_inserter(u), [](int x) { return (x % 2) == 0; });
    std::cout << "u: " << u << std::endl;

    std::vector<int> vpp(10);
    std::generate(vpp.begin(), vpp.end(), [n = 1]() mutable {
        return 20 * n++;
    });
    std::cout << "vpp: " << vpp << std::endl;

    if (std::all_of(std::execution::par, vpp.cbegin(), vpp.cend(), [](int i) { return (i % 2) == 0; }))
        std::cout << "all item of " << vpp << " are Even" << std::endl;
    else
        std::cout << "at least one of " << vpp << " is not Even" << std::endl;
    if (std::none_of(vpp.cbegin(), vpp.cend(), [](int i) { return (i % 2) == 1; }))
        std::cout << "no item of " << vpp << " are Odd" << std::endl;
    else
        std::cout << "at least one of " << vpp << " is Odd" << std::endl;
    if (std::any_of(vpp.cbegin(), vpp.cend(), [](int i) { return (i % 7) == 0; }))
        std::cout << "at least one of " << vpp << " is divisible by 7" << std::endl;
    else
        std::cout << "no item of " << vpp << "is divisible by 7" << std::endl;
    auto result = std::find_if(vpp.cbegin(), vpp.cend(), [](int i) { return (i % 7) == 0; });
    if (result != vpp.cend())
        std::cout << *(result) << " is divisible by 7" << std::endl;

    std::vector<int> random_vector(20);
    std::uniform_int_distribution<> uniformIntDistribution3(-30, 30);
    std::generate(random_vector.begin(), random_vector.end(),
                  [&]() { return uniformIntDistribution3(random_generator); });
    std::cout << "random vect: " << random_vector << std::endl << "sort: " << std::endl;
    std::sort(std::execution::par, random_vector.begin(), random_vector.end());
    std::cout << "random vect: " << random_vector << std::endl;
    std::cout << "greater Sort:" << std::endl;
    std::sort(std::execution::par, random_vector.begin(), random_vector.end(), std::greater());
    std::cout << "random vect: " << random_vector << std::endl;
    std::sort(std::execution::par, random_vector.begin(), random_vector.end(),
              [](int a, int b) { return (a * a) > (b * b); });
    std::cout << "random vect: " << random_vector << std::endl;
    maredduce();*/
    calcul();
    return 0;
}

