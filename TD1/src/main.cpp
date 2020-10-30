//Standard headers
#include <iostream>
#include <vector>

//User defined Headers
#include "common.h"
#include "main.h"

int main(int argc, char *argv[]) {
    std::cout << "argc: " << argc << " argv: ";
    for (auto i = 0; i < argc; i++) std::cout << argv[i] << "\t";
    std::cout << std::endl;
    std::cout << "Hello World!" << std::endl;
    std::vector<int32> y = {1, 3, 5, 7, 9, 11, 13, 15, 17};
    std::vector<int32> x = y;
    y[0] = 66;
    std::cout << "x:\t";
    for (auto k:x)
        std::cout << k << "\t";
    std::cout << std::endl;
    std::cout << "y:\t";
    for (auto k : y)
        std::cout << k << "\t";
    std::cout << std::endl;

    x.swap(y);
    std::cout << "Swap! x<->y" << std::endl;
    std::cout << "x:\t";
    for (int k:x)
        std::cout << k << "\t";
    std::cout << std::endl;
    std::cout << "y:\t";
    for (int k : y)
        std::cout << k << "\t";
    std::cout << std::endl;
    auto Y = std::move(x);
    std::cout << "Move: x->y: X0 " << Y[0] << std::endl;

    return 0;
}
