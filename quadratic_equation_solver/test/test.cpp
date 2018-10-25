#include <iostream>
#include "test.h"

#define pattern  "ответ для теста с параметрами: a = " << a << ", b = " << b << ", c = " << c << "!"

void Test(double a, double b, double c, std::vector<double> solution) {
    if (QuadraticEquationTester(a, b, c).Assert(solution)) {
        std::cout << "Верный " << pattern << std::endl;
    } else {
        std::cout << "Неверный " << pattern << std::endl;
    }
}

#undef pattern

int main() {
    Test(1, 2, 1, {-1});
    Test(0, 0, 0, {});
    Test(1, -4, 3, {1, 3});
    Test(0, 0, 9, {});
    Test(1, 2, 0, {0, -2});
    Test(-3, 6, 0, {2, 0});

    return 0;
}