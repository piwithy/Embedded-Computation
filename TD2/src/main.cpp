#include <iostream>
#include <vector>
#include <complex>
#include <numbers>

using namespace std;
using namespace std::literals;
using namespace std::numbers;

int func1() {
    return 42;
}

int func2(int arg) {
    return arg;
}

double func2(double arg) {
    return arg;
}

template<typename T>
T func3(T arg) {
    return arg;
}

struct FuncObject4 {
    int operator()() { // (1)
        return 1998;
    }
};

auto func5 = [] {
    return 2011;
};


auto func6 = [](auto arg) {
    return arg;
};

template<typename T>
void print_vector(const vector<T> &v) {
    cout << "[";
    for (long unsigned int i = 0; i < v.size(); i++) {
        cout << " " << v.at(i);
        if (i != v.size() - 1)
            cout << ",";
    }
    cout << " ]" << endl;
}

vector<int> getNumbers(int begin, int end, int inc = 1) {
    vector<int> v{};
    for (auto i = begin; i < end; i += inc)
        v.push_back(i);
    return v;
}

complex<double> kth_nth_root_o_unity(int k, int n) {
    complex<double> ret;
    if (k >= 0 && k < n) {
        ret = std::exp(((2 * pi * 1.i * (double) k) / (double) n));
    }
    return ret;
}

vector<complex<double>> nth_root_o_unity(int n) {
    vector<complex<double>> n_root = {};
    n_root.reserve(n);
    for (int k = 0; k < n; k++) {
        n_root.push_back(kth_nth_root_o_unity(k, n));
    }
    return n_root;
}

void functionsEvolution() {
    cout << func1() << endl;            // 42
    cout << func2(1998) << endl;    // 1998
    cout << func2(1998.8) << endl;  // 1998.0
    cout << func3(1998) << endl;    // 1998
    cout << func3(1998.8) << endl;  // 1998.0
    FuncObject4 func4;
    cout << func4() << endl;    // 1998
    cout << func5() << endl;    // 2011
    cout << func6(2014) << endl;    // 2014
    cout << func6(2014.4) << endl;  // 2014
}


int main() {
    cout << "Hello, World!" << endl;
    //functionsEvolution();
    vector<complex<double>> v{1.0 + 1i, 1.7 + 3.i, 3.24 + 1.i};
    print_vector(v);
    vector<int> vi = getNumbers(-3, 10, 2);
    print_vector(vi);
    print_vector(getNumbers(3, 10, 2));
    complex<double> c1 = 1. + 1.i;
    complex<double> c2 = 1. - 1.i;

    cout << "(1+i) + (1-i) = " << c1 + c2 << endl;
    cout << "(1+i) - (1-i) = " << c1 - c2 << endl;
    cout << "(1+i) * (1-i) = " << c1 * c2 << endl;
    cout << "(1+i) / (1-i) = " << c1 / c2 << endl;
    print_vector(nth_root_o_unity(2));
    return 0;
}
