#include "engine.h"
#include <regex>
#include <iostream>

int get_number(const std::vector<std::string>& rows) {
    std::regex number_reg("\\d+");
    int sum = 0;
    for(size_t i = 0; i < rows.size(); i++) {
        std::string curr_row = rows.at(i);

        std::sregex_iterator words_begin(curr_row.begin(), curr_row.end(), number_reg);
        const std::sregex_iterator words_end;

        while(words_begin != words_end) {

            int start = words_begin->position() - 1;
            size_t end = words_begin->position() + words_begin->length();
            if((start >= 0 && curr_row[start] != '.') || (end < curr_row.length() && curr_row[end] != '.')) {
                 sum += std::stoi(words_begin->str());
                 words_begin++;
                 continue;
            }

            if(i+1 < rows.size()) {
                size_t j = (words_begin->position() - 1) < 0 ? 0 : words_begin->position() - 1;
                for (; j <= end; j++) {
                    auto row_to_check = rows[i+1];
                    if(j < row_to_check.length() && row_to_check[j] != '.') {
                        sum += std::stoi(words_begin->str());
                        break;
                    }
                }
            }

            if(i > 0) {
                size_t j = (words_begin->position() - 1) < 0 ? 0 : words_begin->position() - 1;
                for (; j <= end; j++) {
                    auto row_to_check = rows[i-1];
                    if(j < row_to_check.length() && row_to_check[j] != '.') {
                        sum += std::stoi(words_begin->str());
                        break;
                    }
                }
            }

            words_begin++;
        }
    }

    

    return sum;
}

int get_gear_number(const std::vector<std::string>& rows) {
    std::regex number_reg("\\d+");
    std::map<std::string, std::vector<int>> result;
    int sum = 0;
    for(size_t i = 0; i < rows.size(); i++) {
        std::string curr_row = rows.at(i);

        std::sregex_iterator words_begin(curr_row.begin(), curr_row.end(), number_reg);
        const std::sregex_iterator words_end;

        while(words_begin != words_end) {

            int start = words_begin->position() - 1;
            size_t end = words_begin->position() + words_begin->length();
            if(start >= 0 && curr_row[start] == '*') {
                 //sum += std::stoi(words_begin->str());
                 result[{std::to_string(i) + ";" + std::to_string(start)}].push_back(std::stoi(words_begin->str()));
                 words_begin++;
                 continue;
            }

            if(end < curr_row.length() && curr_row[end] == '*') {
                result[{std::to_string(i) + ";" + std::to_string(end)}].push_back(std::stoi(words_begin->str()));
                words_begin++;
                continue;
            }

            if(i+1 < rows.size()) {
                size_t j = (words_begin->position() - 1) < 0 ? 0 : words_begin->position() - 1;
                auto row_to_check = rows[i+1];
                for (; j <= end; j++) {
                    if(j < row_to_check.length() && row_to_check[j] == '*') {
                        result[{std::to_string(i+1) + ";" + std::to_string(j)}].push_back(std::stoi(words_begin->str()));
                    }
                }
            }

            if(i > 0) {
                size_t j = (words_begin->position() - 1) < 0 ? 0 : words_begin->position() - 1;
                auto row_to_check = rows[i-1];
                for (; j <= end; j++) {
                    if(j < row_to_check.length() && row_to_check[j] == '*') {
                        result[{std::to_string(i-1) + ";" + std::to_string(j)}].push_back(std::stoi(words_begin->str()));
                    }
                }
            }

            words_begin++;
        }
    }
    std::cout << result.size() << '\n';
    for(auto ele : result) {
        if (ele.second.size() == 2) {
            sum+=(ele.second[0] * ele.second[1]);
        }
    }

    return sum;
}