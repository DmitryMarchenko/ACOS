#include <iostream>
#include <limits>
#include "solver.h"

/**
 * @brief Input equation coefficients
 *
 * @param a Coefficient link
 * @param name Coefficient name
 */
void input_coeff(double& a, char name) {
    int cnt = 0;
    while (true) {
        try {
            std::cout << name << " = ";
            if (cnt++) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            std::cin >> a;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cout << std::endl;
                throw 1;
            }
            break;
        } catch(int i) {
            std::cout << "Невалидное значение коэффициента " << name << "! "
                      << "Введите число в десятичной записи от " << std::numeric_limits<double>::min()
                      << " до " << std::numeric_limits<double>::max() << std::endl << std::endl;
        }
    }
}


/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */

int main() {
    double a, b, c;
    std::cout << "Введите коэффициенты квадратного уравнения ax^2 + bx + c = 0" << std::endl;

    input_coeff(a, 'a');
    input_coeff(b, 'b');
    input_coeff(c, 'c');

    std::cout << std::endl;

    QuadraticEquation equation(a, b, c);

    std::vector<double> answer = std::move(equation.Solve());

    if (answer.empty()) {
        if (equation.AnyNumber()) {
            std::cout << "Уравнение имеет бесконечно много решений" << std::endl;
        } else {
            std::cout << "Уравнение не имеет решений" << std::endl;
        }
    } else if (answer.size() == 1) {
        std::cout << "Уравнение имеет одно решение" << std::endl;
        std::cout << "X = " << answer[0] << std::endl;
    } else if (answer.size() == 2) {
        std::cout << "Уравнение имеет два решения" << std::endl;
        std::cout << "X_1 = " << answer[0] << std::endl;
        std::cout << "X_2 = " << answer[1] << std::endl;
    } else {
        std::cout << "Упс! Хьюстон, у нас проблемы!" << std::endl;
    }

    return 0;
}
