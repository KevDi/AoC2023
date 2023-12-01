#pragma once
#include <string>

int get_calibration_number(const std::string& calibration_line);
int get_complex_calibration_number(const std::string& calibration_line);
int calculate_calibration(const std::string &file);
int calculate_complex_calibration(const std::string& file);