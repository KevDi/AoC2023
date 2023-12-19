#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

int main() {
    std::ifstream data{"resources/data.txt"};
    std::vector<std::pair<int, int>> grid{{0, 0}};
    std::unordered_map<char, std::pair<int, int>> dirs{
        {'U', {-1, 0}},
        {'D', {1, 0}},
        {'L', {0, -1}},
        {'R', {0, 1}}};
    int b = 0;
    if (data.is_open()) {
        std::string line;

        while (std::getline(data, line)) {
            std::istringstream tokenStream(line);
            std::string token;
            std::string direction;
            std::getline(tokenStream, direction, ' ');
            std::getline(tokenStream, token, ' ');
            int steps = std::stoi(token);
            auto [dr, dc] = dirs[direction[0]];
            b += steps;

            auto [row, col] = grid.back();

            grid.push_back({row + dr * steps, col + dc * steps});
        }
        data.close();
    }
    int sum = 0;
    for (int i = 0; i < grid.size(); i++) {
        sum += (grid[i].first * (grid[i - 1 < 0 ? grid.size() - 1 : i - 1].second - grid[(i + 1) % grid.size()].second));
    }
    sum = std::abs(sum) / 2;
    int result = sum - b / 2 + 1;
    std::cout << result + b << '\n';
}