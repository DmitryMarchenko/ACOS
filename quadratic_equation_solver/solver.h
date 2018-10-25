#pragma once

#include <vector>
#include <cmath>

#define EPS 1e-9

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
        if (equally(a_, 0)) {
            return solve_lin();
        }

        if (equally(c_, 0)) {
            return solve_with_zero_c();
        }

        std::vector<double> answer;

        double D = b_ * b_ - 4 * a_ * c_;

        if (D <= -EPS) {
            return answer;
        }

        if (equally(D, 0)) {
            answer.push_back(rm_negative_of_null(-b_ / 2 / a_));
            return answer;
        }

        answer.push_back(rm_negative_of_null(-b_ + sqrt(D)) / 2 / a_);
        answer.push_back(rm_negative_of_null(-b_ - sqrt(D)) / 2 / a_);

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
        if (!equally(b_, 0)) {
            return std::vector<double>(1, rm_negative_of_null(-c_ / b_));
        } else if (equally(c_, 0)) {
            any_number = true;
        }
        return std::vector<double>(0);
    }

    /**
     * @private
     * @brief Equation without free member solver
     *
     * @return Solution of equation without free member
     */
    std::vector<double> solve_with_zero_c() {
        std::vector<double> answer(2);
        answer.push_back(0);
        answer.push_back(-b_/a_);
        return answer;
    }

    double rm_negative_of_null(double a) {
        if (equally(a, 0)) {
            return 0;
        }
        return a;
    }

    bool equally(double a, double b) {
        return fabs(a - b) < EPS;
    }
};