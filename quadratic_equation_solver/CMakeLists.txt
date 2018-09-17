cmake_minimum_required(VERSION 3.10)
project(quadratic_equation_solver)

set(CMAKE_CXX_STANDARD 11)

add_executable(quadratic_equation_solver solver.h main.cpp)
add_executable(quadratic_equation_solver_tester solver.h test/test.h test/test.cpp )