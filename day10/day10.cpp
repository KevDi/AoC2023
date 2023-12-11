#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum class Direction {
    NORTH,
    SOUTH,
    WEST,
    EAST
};

int main() {
    std::ifstream data{"resources/data.txt"};
    long long steps = 0;
    std::vector<std::string> data_map;
    std::pair<int, int> start;
    std::vector<std::pair<int, int>> pipe;

    std::unordered_set<std::string> result;

    std::unordered_map<Direction, std::string> next_nodes{
        {Direction::NORTH, "|F7S"},
        {Direction::SOUTH, "|LJS"},
        {Direction::EAST, "-7JS"},
        {Direction::WEST, "-LFS"},
    };

    std::unordered_map<Direction, Direction> opposite_map{
        {Direction::NORTH, Direction::SOUTH},
        {Direction::SOUTH, Direction::NORTH},
        {Direction::EAST, Direction::WEST},
        {Direction::WEST, Direction::EAST}};

    std::unordered_map<char, std::pair<Direction, Direction>>
        node_direction{
            {'J', {Direction::NORTH, Direction::WEST}},
            {'|', {Direction::NORTH, Direction::SOUTH}},
            {'L', {Direction::NORTH, Direction::EAST}},
            {'7', {Direction::SOUTH, Direction::WEST}},
            {'F', {Direction::SOUTH, Direction::EAST}},
            {'-', {Direction::WEST, Direction::EAST}},
        };

    if (data.is_open()) {
        std::string line;
        int counter = 0;
        while (std::getline(data, line)) {
            if (auto pos = line.find('S'); pos != std::string::npos) {
                start = {counter, pos};
                pipe.push_back(start);
                result.insert({std::to_string(start.first) + ":" + std::to_string(start.second)});
            }
            data_map.push_back(line);
            counter++;
        }

        data.close();
    }
    char next_char;
    Direction entering_direction;
    Direction start_direction;

    if (size_t pos = next_nodes[Direction::WEST].find(data_map[start.first][start.second - 1]); pos != std::string::npos) {
        next_char = next_nodes[Direction::WEST][pos];
        start = {start.first, start.second - 1};
        entering_direction = Direction::EAST;
        start_direction = Direction::WEST;
    } else if (size_t pos = next_nodes[Direction::EAST].find(data_map[start.first][start.second + 1]); pos != std::string::npos) {
        next_char = next_nodes[Direction::EAST][pos];
        start = {start.first, start.second + 1};
        entering_direction = Direction::WEST;
        start_direction = Direction::EAST;
    } else if (size_t pos = next_nodes[Direction::NORTH].find(data_map[start.first - 1][start.second]); pos != std::string::npos) {
        next_char = next_nodes[Direction::NORTH][pos];
        start = {start.first - 1, start.second};
        entering_direction = Direction::SOUTH;
        start_direction = Direction::NORTH;
    } else if (size_t pos = next_nodes[Direction::SOUTH].find(data_map[start.first + 1][start.second]); pos != std::string::npos) {
        next_char = next_nodes[Direction::SOUTH][pos];
        start = {start.first + 1, start.second};
        entering_direction = Direction::NORTH;
        start_direction = Direction::SOUTH;
    }
    pipe.push_back(start);
    result.insert({std::to_string(start.first) + ":" + std::to_string(start.second)});
    steps++;

    while (next_char != 'S') {
        auto dir = node_direction[next_char].first != entering_direction ? node_direction[next_char].first : node_direction[next_char].second;

        switch (dir) {
            case Direction::NORTH:
                if ((start.first - 1) >= 0) {
                    next_char = data_map[start.first - 1][start.second];
                    entering_direction = Direction::SOUTH;
                    start.first = start.first - 1;
                }
                break;
            case Direction::SOUTH:
                if ((start.first + 1) < data_map.size()) {
                    next_char = data_map[start.first + 1][start.second];
                    entering_direction = Direction::NORTH;
                    start.first = start.first + 1;
                }
                break;
            case Direction::WEST:
                if ((start.second - 1) >= 0) {
                    next_char = data_map[start.first][start.second - 1];
                    entering_direction = Direction::EAST;
                    start.second = start.second - 1;
                }
                break;
            case Direction::EAST:
                if ((start.second + 1) < data_map[start.first].size()) {
                    next_char = data_map[start.first][start.second + 1];
                    entering_direction = Direction::WEST;
                    start.second = start.second + 1;
                }
                break;
        }
        pipe.push_back(start);
        result.insert({std::to_string(start.first) + ":" + std::to_string(start.second)});
        steps++;
    }

    if (start_direction == Direction::NORTH) {
        switch (entering_direction) {
            case Direction::SOUTH:
                data_map[start.first][start.second] = '|';
                break;
            case Direction::WEST:
                data_map[start.first][start.second] = 'J';
                break;
            case Direction::EAST:
                data_map[start.first][start.second] = 'L';
                break;
        }
    } else if (start_direction == Direction::SOUTH) {
        switch (entering_direction) {
            case Direction::NORTH:
                data_map[start.first][start.second] = '|';
                break;
            case Direction::WEST:
                data_map[start.first][start.second] = '7';
                break;
            case Direction::EAST:
                data_map[start.first][start.second] = 'F';
                break;
        }
    } else if (start_direction == Direction::WEST) {
        switch (entering_direction) {
            case Direction::NORTH:
                data_map[start.first][start.second] = 'J';
                break;
            case Direction::SOUTH:
                data_map[start.first][start.second] = '7';
                break;
            case Direction::EAST:
                data_map[start.first][start.second] = '-';
                break;
        }
    } else if (start_direction == Direction::EAST) {
        switch (entering_direction) {
            case Direction::NORTH:
                data_map[start.first][start.second] = 'L';
                break;
            case Direction::SOUTH:
                data_map[start.first][start.second] = 'F';
                break;
            case Direction::WEST:
                data_map[start.first][start.second] = '-';
                break;
        }
    }

    std::cout << steps / 2 << '\n';

    for (auto y = 0; y < data_map.size(); y++) {
        for (auto x = 0; x < data_map[y].size(); x++) {
            if (std::find(pipe.begin(), pipe.end(), std::pair{y, x}) == pipe.end()) {
                data_map[y][x] = '.';
            }
        }
    }

    std::vector<std::pair<int, int>> outside{};
    for (auto y = 0; y < data_map.size(); y++) {
        bool within = false;
        std::unique_ptr<bool> up{nullptr};
        for (auto x = 0; x < data_map[y].size(); x++) {
            switch (data_map[y][x]) {
                case '|':
                    if (up) {
                        throw std::invalid_argument{"Wrong! |"};
                    }
                    within = !within;
                    break;
                case '-':
                    if (!up) {
                        throw std::invalid_argument{"Wrong! -"};
                    }
                    break;
                case 'L':
                case 'F':
                    if (up) {
                        throw std::invalid_argument{"Wrong! LF"};
                    }
                    up = std::make_unique<bool>(data_map[y][x] == 'L');
                    break;
                case '7':
                case 'J':
                    if (!up) {
                        throw std::invalid_argument{"Wrong! 7J"};
                    }
                    if (*up && data_map[y][x] != 'J') {
                        within = !within;
                    } else if (!(*up) && data_map[y][x] != '7') {
                        within = !within;
                    }
                    up.reset(nullptr);
                    break;
                case '.':
                    break;
                default:
                    throw std::invalid_argument{"Wrong! char"};
            }
            if (!within) {
                result.insert({std::to_string(y) + ":" + std::to_string(x)});
            }
        }
    }
    std::cout << data_map.size() * data_map[0].size() - result.size() << '\n';
}