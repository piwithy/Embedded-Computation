#include <iostream>
#include <vector>
#include <iterator>
#include <array>

template<typename T>
std::ostream &operator<<(std::ostream &s, const std::vector<T> &v) {
    s << '[';
    if (!v.empty()) {
        std::copy(v.cbegin(), v.cend() - 1, std::ostream_iterator<T>(s, ", "));
        s << v.back();
    }
    return s << ']';
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<double> vec(10, 0.0);
    std::cout << "vec=" << vec << std::endl;
    for (size_t i = 0; i < 90; i++) {
        vec.push_back(0.);
        std::cout << "vec.size=" << vec.size() << "\t" << "vec.capacity=" << vec.capacity() << "\t" << "vec.max_size="
                  << vec.max_size() << std::endl;
    }
    vec.shrink_to_fit();
    std::cout << "vec=" << vec << std::endl;
    std::cout << "vec.size=" << vec.size() << "\t" << "vec.capacity=" << vec.capacity() << "\t" << "vec.max_size="
              << vec.max_size() << std::endl;
    return 0;
}
