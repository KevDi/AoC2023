#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <set>
#include <vector>

/*
    Many thanks to Simon Toth: https://simontoth.substack.com/p/daily-bite-of-c-advent-of-code-day-35f
    https://github.com/HappyCerberus/aoc-2023-cpp-solutions/tree/main/aoc2023/day17
*/

struct Coord {
    int row;
    int col;

    Coord operator+(const Coord& other) const {
        Coord result = *this;
        result.row += other.row;
        result.col += other.col;
        return result;
    }

    Coord operator*(int scalar) const {
        Coord result = *this;
        result.row *= scalar;
        result.col *= scalar;
        return result;
    }

    bool operator<(const Coord& other) const {
        return row < other.row && col < other.col;
    }

    bool operator==(const Coord& other) const {
        return row == other.row && col == other.col;
    }
};

struct State {
    Coord position;
    Coord direction;
    int steps;
    int heat_loss;
    bool operator<(const State& other) const {
        return heat_loss > other.heat_loss;
    }
};

template <>
struct std::hash<Coord> {
    std::size_t operator()(const Coord& c) const noexcept {
        std::size_t h1 = std::hash<int>{}(c.row);
        std::size_t h2 = std::hash<int>{}(c.col);
        return h1 ^ (h2 << 1);
    }
};

int minimum_heatlos(std::vector<std::string>& grid) {
    auto loss_at = [&](Coord position) {
        return grid[position.row][position.col] - '0';
    };
    // Helper that checks for boundaries
    auto can_step = [&](Coord coord) {
        if (coord.row < 0 || coord.col < 0)
            return false;
        if (coord.row >= grid.size())
            return false;
        if (coord.col >= grid[0].size())
            return false;
        return true;
    };

    auto left_direction = [](Coord direction) {
        if (direction.row != 0)
            return Coord{0, direction.row};
        return Coord{-direction.col, 0};
    };
    auto right_direction = [](Coord direction) {
        if (direction.row != 0)
            return Coord{0, -direction.row};
        return Coord{direction.col, 0};
    };

    constexpr auto max_steps = 10;
    using Best = std::array<std::array<int64_t, max_steps>, 4>;
    std::vector<std::vector<Best>> best(
        grid.size(), std::vector<Best>(grid[0].size(), [] {
            std::array<std::array<int64_t, max_steps>, 4> result;
            for (auto& direction : result)
                for (auto& distance : direction)
                    distance = INT64_MAX;
            return result;
        }()));

    // Helper that returns an index in the above structure for the given
    // direction
    auto dir_to_int = [&](Coord direction) {
        if (direction.row == -1)
            return 0;
        if (direction.row == 1)
            return 1;
        if (direction.col == -1)
            return 2;
        return 3;
    };

    // BFS with a priority queue (a.k.a. mostly Dijkstra)
    std::priority_queue<State> q;
    Coord destination = {grid.size() - 1, grid[0].size() - 1};

    // Helper that adds a given state to the queue if it is better than our best
    // known for that position, direction and remaining steps
    auto push_if_better = [&](State s) {
        if (best[s.position.row][s.position.col][dir_to_int(s.direction)]
                [s.steps - 1] > s.heat_loss) {
            best[s.position.row][s.position.col][dir_to_int(s.direction)]
                [s.steps - 1] = s.heat_loss;
            q.push(s);
        }
    };

    // Two starting states, {0,0}, going right and down
    // Note that steps == 0 and heat_loss == 0
    push_if_better({{0, 0}, {1, 0}, 0, 0});
    push_if_better({{0, 0}, {0, 1}, 0, 0});

    while (not q.empty()) {
        auto [pos, dir, steps, heat_loss] = q.top();
        // If we are at our destination, report the heat_loss, because of the
        // priority queue we have a guarantee this is the minimum value
        if (pos == destination)
            return heat_loss;
        q.pop();

        // We can go at most 10 steps straight
        if (steps < 10 && can_step(pos + dir))
            push_if_better(
                {pos + dir, dir, steps + 1, heat_loss + loss_at(pos + dir)});
        // We can only turn after 4 steps, also we need to make sure we do not run
        // into wall after turning
        if (steps >= 4) {
            if (can_step(pos + left_direction(dir) * 4))
                push_if_better({pos + left_direction(dir), left_direction(dir), 1,
                                heat_loss + loss_at(pos + left_direction(dir))});
            if (can_step(pos + right_direction(dir) * 4))
                push_if_better({pos + right_direction(dir), right_direction(dir), 1,
                                heat_loss + loss_at(pos + right_direction(dir))});
        }
    }
    return 0;
}

int main() {
    std::ifstream data{"resources/data.txt"};
    std::vector<std::string> grid;
    if (data.is_open()) {
        std::string line;

        while (std::getline(data, line)) {
            grid.push_back(line);
        }
        data.close();
    }

    std::cout << minimum_heatlos(grid);
}