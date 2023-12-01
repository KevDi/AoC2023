#include "day01.h"
#include <iostream>

int main() {
    std::cout << calculate_calibration("resources/data.txt") << '\n';
    std::cout << calculate_complex_calibration("resources/data.txt") << '\n';
}