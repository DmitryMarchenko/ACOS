#pragma once

#include "../solver.h"
#include <algorithm>

class QuadraticEquationTester {
public:
    QuadraticEquationTester(double a, double b, double c) : equation(a, b, c) {}

    bool Assert(std::vector<double>& solution) {
        std::vector<double> answer = std::move(equation.Solve());
        std::sort(solution.begin(), solution.end());
        std::sort(answer.begin(), answer.end());
        return solution == answer;
    }

private:
    QuadraticEquation equation;
};