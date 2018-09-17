#include <iostream>
#include "test.h"

void Test(double a, double b, double c, std::vector<double> solution) {
    if (QuadraticEquationTester(a, b, c).Assert(solution)) {
        std::cout << "Верный ответ для теста с параметрами " << a << " " << b << " " << c << "!" << std::endl;
        std::cout <<std::endl;
    } else {
        std::cout << "Нерный ответ для теста с параметрами " << a << " " << b << " " << c << "!" << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    Test(1, 2, 1, {-1});
    Test(0, 0, 0, {});
    Test(1, -4, 3, {1, 3});
    Test(0, 0, 9, {});

    return 0;
}