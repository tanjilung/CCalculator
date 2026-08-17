#include <cassert>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "math_utils.h"

static bool approx(double a, double b) {
    return std::fabs(a - b) < 1e-9;
}

void test_add() {
    assert(approx(add(2.0, 3.0), 5.0));
    assert(approx(add(-1.0, 1.0), 0.0));
    assert(approx(add(0.0, 0.0), 0.0));
    std::cout << "[PASS] test_add" << std::endl;
}

void test_subtract() {
    assert(approx(subtract(10.0, 4.0), 6.0));
    assert(approx(subtract(0.0, 0.0), 0.0));
    assert(approx(subtract(-5.0, -3.0), -2.0));
    std::cout << "[PASS] test_subtract" << std::endl;
}

void test_multiply() {
    assert(approx(multiply(5.0, 6.0), 30.0));
    assert(approx(multiply(0.0, 100.0), 0.0));
    assert(approx(multiply(-2.0, 3.0), -6.0));
    std::cout << "[PASS] test_multiply" << std::endl;
}

void test_divide() {
    assert(approx(divide(10.0, 2.0), 5.0));
    assert(approx(divide(7.0, 3.0), 2.333333333333333));
    assert(approx(divide(-6.0, 2.0), -3.0));

    bool caught = false;
    try {
        divide(1.0, 0.0);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    assert(caught && "divide() should throw on division by zero");

    std::cout << "[PASS] test_divide" << std::endl;
}

int main() {
    test_add();
    test_subtract();
    test_multiply();
    test_divide();

    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
