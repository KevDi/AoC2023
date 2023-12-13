#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int count(std::string config, std::vector<int> numbers) {
    if (config.empty()) {
        return numbers.empty() ? 1 : 0;
    }

    if (numbers.empty()) {
        return config.find('#') != std::string::npos ? 0 : 1;
    }

    int result = 0;

    if (std::string{".?"}.find(config[0]) != std::string::npos) {
        result += count(config.substr(1), numbers);
    }

    if (std::string{"#?"}.find(config[0]) != std::string::npos) {
        if (numbers[0] <= config.size() && config.substr(0, numbers[0]).find('.') == std::string::npos && (numbers[0] == config.size() || config[numbers[0]] != '#')) {
            auto config_sub = numbers[0] + 1 >= config.size() ? std::string{} : config.substr(numbers[0] + 1);
            numbers.erase(numbers.begin());
            result += count(config_sub, numbers);
        }
    }

    return result;
}

int main() {
    std::ifstream data{"resources/data.txt"};
    std::string instructions;

    int total = 0;
    if (data.is_open()) {
        std::string line;
        while (std::getline(data, line)) {
            std::istringstream tokenStream(line);
            std::vector<int> nums;
            std::string token;
            std::getline(tokenStream, instructions, ' ');
            while (std::getline(tokenStream, token, ',')) {
                nums.push_back(std::stoi(token));
            }
            int arr = count(instructions, nums);
            total += arr;
        }
    }
    std::cout << total << '\n';
    data.close();
}