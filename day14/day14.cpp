#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::string serialize_state(const std::vector<std::pair<int, int>>& r_rocks) {
    std::string result;

    for (auto ele : r_rocks) {
        result.append(std::to_string(ele.first) + std::to_string(ele.second));
    }

    return result;
}

void print(const std::vector<std::pair<int, int>>& r_rocks, const std::vector<std::pair<int, int>>& c_rocks, int height, int length) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < length; j++) {
            if (std::find(r_rocks.begin(), r_rocks.end(), std::pair<int, int>(i, j)) != r_rocks.end()) {
                std::cout << 'O';
            } else if (std::find(c_rocks.begin(), c_rocks.end(), std::pair<int, int>(i, j)) != c_rocks.end()) {
                std::cout << '#';
            } else {
                std::cout << '.';
            }
        }

        std::cout << '\n';
    }
}

int main() {
    std::ifstream data{"resources/data.txt"};
    std::vector<std::pair<int, int>> rounded_rocks{};
    std::vector<std::pair<int, int>> cube_rocks{};
    int length = 0;
    size_t line_length = 0;
    if (data.is_open()) {
        std::string line;
        while (std::getline(data, line)) {
            line_length = line.size();
            for (int i = 0; i < line.size(); i++) {
                if (line[i] == 'O') {
                    rounded_rocks.push_back({length, i});
                }

                if (line[i] == '#') {
                    cube_rocks.push_back({length, i});
                }
            }
            length++;
        }

        data.close();
    }

    std::unordered_map<std::string, long> cycleMap;
    std::vector<std::vector<std::pair<int, int>>> grids;
    long cycle = 0;
    for (; cycle < 1000000000; cycle++) {
        for (auto& ele : rounded_rocks) {
            for (int i = ele.first - 1; i >= 0; i--) {
                if (std::find(rounded_rocks.begin(), rounded_rocks.end(), std::pair<int, int>{i, ele.second}) == rounded_rocks.end() && std::find(cube_rocks.begin(), cube_rocks.end(), std::pair<int, int>{i, ele.second}) == cube_rocks.end()) {
                    ele.first = i;
                } else {
                    break;
                }
            }
        }

        // print(rounded_rocks, cube_rocks, length, line_length);

        std::sort(rounded_rocks.begin(), rounded_rocks.end());

        for (auto& ele : rounded_rocks) {
            for (int i = ele.second - 1; i >= 0; i--) {
                if (std::find(rounded_rocks.begin(), rounded_rocks.end(), std::pair<int, int>{ele.first, i}) == rounded_rocks.end() && std::find(cube_rocks.begin(), cube_rocks.end(), std::pair<int, int>{ele.first, i}) == cube_rocks.end()) {
                    ele.second = i;
                } else {
                    break;
                }
            }
        }
        // std::cout << '\n';
        //(rounded_rocks, cube_rocks, length, line_length);

        std::sort(rounded_rocks.rbegin(), rounded_rocks.rend());

        for (auto& ele : rounded_rocks) {
            for (int i = ele.first + 1; i < length; i++) {
                if (std::find(rounded_rocks.begin(), rounded_rocks.end(), std::pair<int, int>{i, ele.second}) == rounded_rocks.end() && std::find(cube_rocks.begin(), cube_rocks.end(), std::pair<int, int>{i, ele.second}) == cube_rocks.end()) {
                    ele.first = i;
                } else {
                    break;
                }
            }
        }
        // std::cout << '\n';
        // print(rounded_rocks, cube_rocks, length, line_length);
        std::sort(rounded_rocks.rbegin(), rounded_rocks.rend());

        for (auto& ele : rounded_rocks) {
            for (int i = ele.second + 1; i < length; i++) {
                if (std::find(rounded_rocks.begin(), rounded_rocks.end(), std::pair<int, int>{ele.first, i}) == rounded_rocks.end() && std::find(cube_rocks.begin(), cube_rocks.end(), std::pair<int, int>{ele.first, i}) == cube_rocks.end()) {
                    ele.second = i;
                } else {
                    break;
                }
            }
        }
        std::sort(rounded_rocks.begin(), rounded_rocks.end());
        // std::cout << serialize_state(rounded_rocks) << '\n';
        auto it = cycleMap.find(serialize_state(rounded_rocks));

        if (it != cycleMap.end()) {
            break;
        }

        cycleMap.insert({serialize_state(rounded_rocks), cycle});
        grids.push_back(rounded_rocks);
    }

    auto grid_it = std::find(grids.begin(), grids.end(), rounded_rocks);
    auto idx = std::distance(grids.begin(), grid_it);

    auto res_idx = (1000000000 - idx) % (cycle - idx) + idx;
    auto res_grid = grids[res_idx - 1];
    std::cout << res_idx << '\n';
    print(res_grid, cube_rocks, length, line_length);
    int sum = 0;
    for (auto& ele : res_grid) {
        sum += length - ele.first;
    }

    std::cout << sum << '\n';
}