#include "day01.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


const std::string NUMBER_LIST{"0123456789"};
const std::vector<std::string> NUMBERS_AS_TEXT{
    {"zero"}, {"one"}, {"two"}, {"three"}, {"four"}, {"five"}, {"six"}, {"seven"}, {"eight"}, {"nine"}
};

int get_calibration_number(const std::string &calibration_line)
{
    auto first_number = calibration_line.at(calibration_line.find_first_of(NUMBER_LIST));
    auto last_number = calibration_line.at(calibration_line.find_last_of(NUMBER_LIST));

    return std::stoi(std::string{first_number, last_number});
}

int get_complex_calibration_number(const std::string& calibration_line) {
    size_t start_idx = calibration_line.size();
    size_t end_idx = 0;
    int first = 0;
    int last = 0;

    
    if (size_t tmp_idx = calibration_line.find_first_of(NUMBER_LIST); tmp_idx != std::string::npos) {
        start_idx = tmp_idx;
        first = calibration_line.at(tmp_idx) - '0';
    }

    if (size_t tmp_idx = calibration_line.find_last_of(NUMBER_LIST); tmp_idx != std::string::npos) {
        end_idx = tmp_idx;
        last = calibration_line.at(tmp_idx) - '0';
    }

    for (size_t i = 0; i < NUMBERS_AS_TEXT.size(); i++) {
        auto curr_idx = calibration_line.find(NUMBERS_AS_TEXT.at(i));
        if (curr_idx != std::string::npos && curr_idx < start_idx) {
            start_idx = curr_idx;
            first = i;
        }
        
        curr_idx = calibration_line.rfind(NUMBERS_AS_TEXT.at(i));
        if (curr_idx != std::string::npos && curr_idx > end_idx) {
            end_idx = curr_idx;
            last = i;
        }
    }

    return first * 10 + last;

}

int calculate_calibration(const std::string &file)
{
    std::ifstream data{file};
    int sum = 0;
    if (data.is_open())
    {
        std::string line;
        while (std::getline(data, line))
        {
            sum+=get_calibration_number(line);
        }
        data.close();
    }
    return sum;
}

int calculate_complex_calibration(const std::string &file)
{
    std::ifstream data{file};
    int sum = 0;
    if (data.is_open())
    {
        std::string line;
        while (std::getline(data, line))
        {
            sum+=get_complex_calibration_number(line);
        }
        data.close();
    }
    return sum;
}