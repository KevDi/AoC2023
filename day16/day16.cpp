#include <algorithm>
#include <fstream>
#include <future>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
struct Element {
    int x{0};
    int y{0};
    Direction direction{Direction::RIGHT};

    std::string string() const {
        return std::to_string(x) + ":" + std::to_string(y);
    }
};

size_t enpower_beams(const std::vector<std::string>& grid, int start_x, int start_y, Direction direction) {
    std::stack<Element> working_stack{};
    std::unordered_map<std::string, int> visited;
    std::set<std::pair<int, int>> result_list{};
    int line_length = grid[0].size();

    working_stack.push({start_x, start_y, direction});

    result_list.insert({start_x, start_y});

    while (!working_stack.empty()) {
        auto working_element = working_stack.top();
        working_stack.pop();

        if (working_element.x < 0 || working_element.x >= grid.size() || working_element.y < 0 || working_element.y >= line_length) {
            continue;
        }

        auto& current_line = grid[working_element.x < 0 ? 0 : working_element.x];

        switch (working_element.direction) {
            case Direction::UP:
                for (; working_element.x >= 0; working_element.x--) {
                    auto curr_ele = grid[working_element.x][working_element.y];
                    result_list.insert({working_element.x, working_element.y});
                    if (curr_ele == '/') {
                        working_stack.push({working_element.x, working_element.y + 1, Direction::RIGHT});
                        break;
                    } else if (curr_ele == '\\') {
                        working_stack.push({working_element.x, working_element.y - 1, Direction::LEFT});
                        break;
                    } else if (curr_ele == '-') {
                        if (visited.find(working_element.string()) == visited.end()) {
                            working_stack.push({working_element.x, working_element.y - 1, Direction::LEFT});
                            working_stack.push({working_element.x, working_element.y + 1, Direction::RIGHT});
                            visited[working_element.string()]++;
                        }
                        break;
                    }
                }
                break;

            case Direction::DOWN:
                for (; working_element.x < grid.size(); working_element.x++) {
                    auto curr_ele = grid[working_element.x][working_element.y];
                    result_list.insert({working_element.x, working_element.y});
                    if (curr_ele == '/') {
                        working_stack.push({working_element.x, working_element.y - 1, Direction::LEFT});
                        break;
                    } else if (curr_ele == '\\') {
                        working_stack.push({working_element.x, working_element.y + 1, Direction::RIGHT});
                        break;
                    } else if (curr_ele == '-') {
                        if (visited.find(working_element.string()) == visited.end()) {
                            working_stack.push({working_element.x, working_element.y - 1, Direction::LEFT});
                            working_stack.push({working_element.x, working_element.y + 1, Direction::RIGHT});
                            visited[working_element.string()]++;
                        }
                        break;
                    }
                }
                break;

            case Direction::RIGHT:
                for (; working_element.y < grid[working_element.x].size(); working_element.y++) {
                    auto curr_ele = grid[working_element.x][working_element.y];
                    result_list.insert({working_element.x, working_element.y});
                    if (curr_ele == '/') {
                        working_stack.push({working_element.x - 1, working_element.y, Direction::UP});
                        break;
                    } else if (curr_ele == '\\') {
                        working_stack.push({working_element.x + 1, working_element.y, Direction::DOWN});
                        break;
                    } else if (curr_ele == '|') {
                        if (visited.find(working_element.string()) == visited.end()) {
                            visited[working_element.string()]++;
                            working_stack.push(Element{working_element.x - 1, working_element.y, Direction::UP});
                            working_stack.push(Element{working_element.x + 1, working_element.y, Direction::DOWN});
                        }

                        break;
                    }
                }
                break;

            case Direction::LEFT:
                for (; working_element.y >= 0; working_element.y--) {
                    auto curr_ele = grid[working_element.x][working_element.y];
                    result_list.insert({working_element.x, working_element.y});
                    if (curr_ele == '/') {
                        working_stack.push({working_element.x + 1, working_element.y, Direction::DOWN});
                        break;
                    } else if (curr_ele == '\\') {
                        working_stack.push({working_element.x - 1, working_element.y, Direction::UP});
                        break;
                    } else if (curr_ele == '|') {
                        if (visited.find(working_element.string()) == visited.end()) {
                            working_stack.push({working_element.x - 1, working_element.y, Direction::UP});
                            working_stack.push({working_element.x + 1, working_element.y, Direction::DOWN});
                            visited[working_element.string()]++;
                        }
                        break;
                    }
                }
                break;
        }
    }

    return result_list.size();
}

int main() {
    std::ifstream data{"resources/data.txt"};
    std::vector<std::string> grid;
    std::stack<Element> working_stack{};
    std::unordered_map<std::string, int> visited;
    std::set<std::pair<int, int>> result_list{};
    std::vector<std::future<size_t>> fut;
    if (data.is_open()) {
        std::string line;

        while (std::getline(data, line)) {
            grid.push_back(line);
        }

        data.close();
    }

    for (int i = 0; i < grid[0].size(); i++) {
        fut.push_back(std::async(std::launch::async, enpower_beams, grid, 0, i, Direction::DOWN));
    }

    for (int i = 0; i < grid.size(); i++) {
        fut.push_back(std::async(std::launch::async, enpower_beams, grid, i, 0, Direction::RIGHT));
    }

    for (int i = 0; i < grid[0].size(); i++) {
        fut.push_back(std::async(std::launch::async, enpower_beams, grid, grid.size() - 1, i, Direction::UP));
    }

    for (int i = 0; i < grid.size(); i++) {
        fut.push_back(std::async(std::launch::async, enpower_beams, grid, i, grid[0].size() - 1, Direction::LEFT));
    }

    size_t max = 0;
    for (auto&& fut_cals : fut) {
        auto res = fut_cals.get();
        max = res > max ? res : max;
    }

    std::cout << max << '\n';
}