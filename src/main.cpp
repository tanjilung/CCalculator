#include <iostream>
#include "math_utils.h"

int main() {
    std::cout << "Hello from CTest!" << std::endl;
    std::cout << "2 + 3 = " << add(2, 3) << std::endl;
    std::cout << "10 - 4 = " << subtract(10, 4) << std::endl;
    std::cout << "5 * 6 = " << multiply(5, 6) << std::endl;
    return 0;
}
