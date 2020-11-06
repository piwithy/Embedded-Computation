//
// Created by jezegoup on 06/11/2020.
//
#include <iostream>
#include <functional>

void capture() {
    int factor = 3;
    std::function<void(void)> l = []() { std::cout << "Proud to be Lambda !" << std::endl; };
    std::function<void(void)> lv = [factor]() mutable { std::cout << "++Factor= " << ++factor << std::endl; };
    l();
    lv();
}


int main(int argc, char *argv[]) {
    std::cout << "Hello World!" << std::endl;
    capture();
    auto div_7 = [](int n) -> bool { return (n % 7) == 0; };
    auto div_n = [](int d, int n) -> bool { return (d % n) == 0; };
    std::cout << "8 div 7 ? " << std::boolalpha << div_7(8) << std::endl;
    std::cout << "42 div 2 ? " << div_n(42, 2) << std::endl;
    return 0;
}
