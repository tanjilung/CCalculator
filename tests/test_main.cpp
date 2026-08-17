#include <cassert>
#include <iostream>
#include "math_utils.h"

void test_add() {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    assert(add(0, 0) == 0);
    std::cout << "[PASS] test_add" << std::endl;
}

void test_subtract() {
    assert(subtract(10, 4) == 6);
    assert(subtract(0, 0) == 0);
    assert(subtract(-5, -3) == -2);
    std::cout << "[PASS] test_subtract" << std::endl;
}

void test_multiply() {
    assert(multiply(5, 6) == 30);
    assert(multiply(0, 100) == 0);
    assert(multiply(-2, 3) == -6);
    std::cout << "[PASS] test_multiply" << std::endl;
}

int main() {
    test_add();
    test_subtract();
    test_multiply();

    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}
