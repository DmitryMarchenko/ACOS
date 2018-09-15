#pragma once

#include <vector>
#include <cmath>

/**
 * @class QuadraticEquation
 *
 * Quadratic equation solver
 */
class QuadraticEquation {
public:
    explicit QuadraticEquation(double a, double b, double c) : a_(a), b_(b), c_(c), any_number(false) {}

    /**
     * @brief Quadratic equation solver
     *
     * @return Solution of quadratic equation
     */
    std::vector<double> Solve() {
        if (a_ == 0) {
            return solve_lin();
        }

        std::vector<double> answer;

        double D = b_ * b_ - 4 * a_ * c_;

        if (D < 0) {
            return answer;
        }

        if (D == 0) {
            answer.push_back(-b_ / 2 / a_);
            return answer;
        }

        answer.push_back((-b_ + sqrt(D)) / 2 / a_);
        answer.push_back((-b_ - sqrt(D)) / 2 / a_);

        return answer;
    }

    /**
     * @brief Any number is solution
     *
     * @return True if any number is solution,
     * else false.
     */
    bool AnyNumber() {
        return any_number;
    }

private:
    double a_, b_, c_;

    bool any_number;

    /**
     * @private
     * @brief Linear equation solver
     *
     * @return Solution of linear equation
     */
    std::vector<double> solve_lin() {
        if (b_ != 0) {
            return std::vector<double>(1, -c_ / b_);
        } else if (c_ == 0) {
            any_number = true;
        }
        return std::vector<double>(0);
    }
};