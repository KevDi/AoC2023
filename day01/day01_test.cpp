#include <gmock/gmock.h>
#include <filesystem>
#include "day01.h"

using namespace testing;

TEST(Day01, ReturnsTheFoundCalibrationValue) {
    std::string test_line{"1abc2"};
    std::string test_line_2{"pqr3stu8vwx"};
    std::string test_line_3{"a1b2c3d4e5f"};
    std::string test_line_4{"treb7uchet"};
    std::string test_line_5{"abcone2threexyz"};


    ASSERT_THAT(get_calibration_number(test_line), Eq(12));
    ASSERT_THAT(get_calibration_number(test_line_2), Eq(38));
    ASSERT_THAT(get_calibration_number(test_line_3), Eq(15));
    ASSERT_THAT(get_calibration_number(test_line_4), Eq(77));
    ASSERT_THAT(get_calibration_number(test_line_5), Eq(22));
}

TEST(Day01, ReturnsCalibrationValue) {
    std::string file_1{"resources/test.txt"};

    ASSERT_THAT(calculate_calibration(file_1), Eq(142));
}

TEST(Day01, GetComplexCalibrationNumberReturnsValue) {
    std::string test_line{"two1nine"};
    std::string test_line_2{"eightwothree"};
    std::string test_line_3{"abcone2threexyz"};
    std::string test_line_4{"xtwone3four"};
    std::string test_line_5{"4nineeightseven2"};
    std::string test_line_6{"zoneight234"};
    std::string test_line_7{"7pqrstsixteen"};
    std::string test_line_8{"32fivefivexjvckfourseven5seven"};

    ASSERT_THAT(get_complex_calibration_number(test_line), Eq(29));
    ASSERT_THAT(get_complex_calibration_number(test_line_2), Eq(83));
    ASSERT_THAT(get_complex_calibration_number(test_line_3), Eq(13));
    ASSERT_THAT(get_complex_calibration_number(test_line_4), Eq(24));
    ASSERT_THAT(get_complex_calibration_number(test_line_5), Eq(42));
    ASSERT_THAT(get_complex_calibration_number(test_line_6), Eq(14));
    ASSERT_THAT(get_complex_calibration_number(test_line_7), Eq(76));
    ASSERT_THAT(get_complex_calibration_number(test_line_8), Eq(37));
}

TEST(Day01, ReturnsComplexCalibrationValue) {
    std::string file_1("resources/test_2.txt");

    ASSERT_THAT(calculate_complex_calibration(file_1), Eq(281));
}