#include <gmock/gmock.h>
#include "engine.h"

using namespace testing;

TEST(Day03, GetNumberReturnsNumberIfSymbolIsAfterOrBeforeNumber) {
    ASSERT_THAT(get_number({"617*......"}), Eq(617));
    ASSERT_THAT(get_number({"+6........"}), Eq(6));
    ASSERT_THAT(get_number({"...67+...."}), Eq(67));
    ASSERT_THAT(get_number({"..+67....."}), Eq(67));
    ASSERT_THAT(get_number({"11+67....."}), Eq(78));
}

TEST(Day03, GetNumberReturnsZeroIfOnlyAdotIsAfterOrBeforeNumber) {
    ASSERT_THAT(get_number({"617......."}), Eq(0));
    ASSERT_THAT(get_number({".617......"}), Eq(0));
}

TEST(Day03, GetNumberReturnsNumberIfSymbolIsUnderNumber) {
    std::vector<std::string> rows{
        {"..35..633."},
        {"......#..."}
    };

    std::vector<std::string> rows_2{
        {"..35..633."},
        {".......#.."}
    };

    std::vector<std::string> rows_3{
        {"..35..633."},
        {"........#."}
    };

    std::vector<std::string> rows_4{
        {"..35..633."},
        {".........#"}
    };

    std::vector<std::string> rows_5{
        {"..35..633."},
        {".....#...."}
    };

    std::vector<std::string> rows_6{
        {"..35..633"},
        {"........#"}
    };

    std::vector<std::string> rows_7{
        {"633"},
        {"#.."}
    };

    ASSERT_THAT(get_number(rows), Eq(633));
    ASSERT_THAT(get_number(rows_2), Eq(633));
    ASSERT_THAT(get_number(rows_3), Eq(633));
    ASSERT_THAT(get_number(rows_4), Eq(633));
    ASSERT_THAT(get_number(rows_5), Eq(633));
    ASSERT_THAT(get_number(rows_6), Eq(633));
    ASSERT_THAT(get_number(rows_7), Eq(633));
}

TEST(Day03, GetNumberReturnsNumberIfSymbolIsAboveNumber) {
    std::vector<std::string> rows{
        {"......#..."},
        {"..35..633."}
    };

    std::vector<std::string> rows_2{
        {".......#.."},
        {"..35..633."}

    };

    std::vector<std::string> rows_3{
        {"........#."},
        {"..35..633."}
    };

    std::vector<std::string> rows_4{
        {".........#"},
        {"..35..633."}
    };

    std::vector<std::string> rows_5{
        {".....#...."},
        {"..35..633."}
    };

    std::vector<std::string> rows_6{
        {"........#"},
        {"..35..633"}
    };

    std::vector<std::string> rows_7{
        {"#.."},
        {"633"}
    };

    ASSERT_THAT(get_number(rows), Eq(633));
    ASSERT_THAT(get_number(rows_2), Eq(633));
    ASSERT_THAT(get_number(rows_3), Eq(633));
    ASSERT_THAT(get_number(rows_4), Eq(633));
    ASSERT_THAT(get_number(rows_5), Eq(633));
    ASSERT_THAT(get_number(rows_6), Eq(633));
    ASSERT_THAT(get_number(rows_7), Eq(633));
}

TEST(Day03, GetNumberReturnsSumOfAllNumbers) {
    ASSERT_THAT(get_number({"617*.11+.."}), Eq(628));

    std::vector<std::string> rows{
        {"467..114.."},
        {"...*......"},
        {"..35..633."},
        {"......#..."},
        {"617*......"},
        {".....+.58."},
        {"..592....."},
        {"......755."},
        {"...$.*...."},
        {".664.598.."}
    };

    ASSERT_THAT(get_number(rows), Eq(4361));
}