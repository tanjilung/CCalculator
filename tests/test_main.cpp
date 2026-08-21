#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

#include "math_utils.h"

static int g_failures = 0;

static void check(bool cond, const char* what) {
    if (cond) {
        std::printf("[ OK ] %s\n", what);
    } else {
        std::printf("[FAIL] %s\n", what);
        ++g_failures;
    }
}

#define CHECK_TRUE(cond, what) check((cond), (what))
#define CHECK_APPROX(a, b, what) check(std::fabs((a) - (b)) < 1e-9, (what))

static void test_add() {
    CHECK_APPROX(calc::add(2.0, 3.0), 5.0, "add(2, 3) == 5");
    CHECK_APPROX(calc::add(-1.0, 1.0), 0.0, "add(-1, 1) == 0");
    CHECK_APPROX(calc::add(0.0, 0.0), 0.0, "add(0, 0) == 0");
}

static void test_subtract() {
    CHECK_APPROX(calc::subtract(10.0, 4.0), 6.0, "subtract(10, 4) == 6");
    CHECK_APPROX(calc::subtract(0.0, 0.0), 0.0, "subtract(0, 0) == 0");
    CHECK_APPROX(calc::subtract(-5.0, -3.0), -2.0, "subtract(-5, -3) == -2");
}

static void test_multiply() {
    CHECK_APPROX(calc::multiply(5.0, 6.0), 30.0, "multiply(5, 6) == 30");
    CHECK_APPROX(calc::multiply(0.0, 100.0), 0.0, "multiply(0, 100) == 0");
    CHECK_APPROX(calc::multiply(-2.0, 3.0), -6.0, "multiply(-2, 3) == -6");
}

static void test_divide() {
    CHECK_APPROX(calc::divide(10.0, 2.0), 5.0, "divide(10, 2) == 5");
    CHECK_APPROX(calc::divide(7.0, 3.0), 2.333333333333333, "divide(7, 3) ~= 7/3");
    CHECK_APPROX(calc::divide(-6.0, 2.0), -3.0, "divide(-6, 2) == -3");

    bool caught = false;
    try {
        calc::divide(1.0, 0.0);
    } catch (const std::invalid_argument&) {
        caught = true;
    }
    CHECK_TRUE(caught, "divide(1, 0) throws std::invalid_argument");
}

int main() {
    test_add();
    test_subtract();
    test_multiply();
    test_divide();

    if (g_failures == 0) {
        std::printf("\nAll tests passed!\n");
        return 0;
    }
    std::printf("\n%d test(s) FAILED\n", g_failures);
    return 1;
}
