#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream data{"resources/data.txt"};
    std::vector<std::pair<long, long>> grid{{0, 0}};
    std::unordered_map<char, std::pair<long, long>> dirs{
        {'U', {-1L, 0L}},
        {'D', {1L, 0L}},
        {'L', {0L, -1L}},
        {'R', {0L, 1L}}};
    long b = 0;
    if (data.is_open()) {
        std::string line;
        std::string pos_dirs{"RDLU"};
        while (std::getline(data, line)) {
            std::istringstream tokenStream(line);
            std::stringstream ss;
            std::string token;
            std::string direction;
            std::getline(tokenStream, direction, ' ');
            std::getline(tokenStream, direction, ' ');
            std::getline(tokenStream, direction, ' ');

            direction = direction.substr(2, direction.size() - 3);
            int curr_dir = direction.back() - '0';
            auto [dr, dc] = dirs[pos_dirs[curr_dir]];

            ss << std::hex << direction.substr(0, direction.size() - 1);
            int steps;
            ss >> steps;
            b += steps;
            auto [row, col] = grid.back();
            grid.push_back({row + dr * steps, col + dc * steps});
        }
        data.close();
    }
    long sum = 0;
    for (int i = 0; i < grid.size(); i++) {
        sum += (grid[i].first * (grid[i - 1 < 0 ? grid.size() - 1 : i - 1].second - grid[(i + 1) % grid.size()].second));
    }
    sum = std::abs(sum) / 2;
    long result = sum - b / 2 + 1;
    std::cout << result + b << '\n';
}