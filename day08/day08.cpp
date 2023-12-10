#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>

int main() {
    std::ifstream data{"resources/data.txt"};
    long long steps = 0;
    std::map<std::string, std::pair<std::string, std::string>> network_map;
    std::vector<std::string> starting_nodes;
    std::string instructions;
    if (data.is_open()) {
        std::string line;
        std::regex network_reg("(\\w+)\\s=\\s\\((\\w+),\\s(\\w+)\\)");
        std::smatch smatch;
        std::getline(data, line);

        instructions = line;

        std::getline(data, line);
        while (std::getline(data, line)) {
            if (std::regex_match(line, smatch, network_reg)) {
                if (smatch.size() != 4) {
                    throw std::invalid_argument{"Wrong input"};
                }

                network_map[smatch[1].str()] = {smatch[2].str(), smatch[3].str()};
                if (smatch[1].str().back() == 'A') {
                    starting_nodes.push_back(smatch[1].str());
                }
            }
        }

        data.close();
    }

    std::string start = "AAA";
    for (int i = 0; i <= instructions.size(); i++) {
        if (start == "ZZZ") {
            break;
        }

        if (i == instructions.size()) {
            i = 0;
        }

        if (instructions[i] == 'L') {
            start = network_map[start].first;
        } else {
            start = network_map[start].second;
        }
        steps++;
    }

    std::cout << steps << '\n';
    steps = 0;

    std::vector<long long> stepsToEnd(starting_nodes.size(), 0);

    for (int i = 0; i <= instructions.size(); i++) {
        steps++;
        if (i == instructions.size()) {
            i = 0;
        }

        for (int j = 0; j < starting_nodes.size(); j++) {
            if (stepsToEnd[j] > 0LL) {
                continue;
            }

            std::string& current = starting_nodes[j];
            current = instructions[i] == 'L' ? network_map[current].first : network_map[current].second;

            if (current.back() == 'Z') {
                stepsToEnd[j] = steps;
            }
        }

        if (std::all_of(stepsToEnd.begin(), stepsToEnd.end(), [](long long val) { return val > 0LL; })) {
            break;
        }
    }

    auto res = std::accumulate(stepsToEnd.begin(), stepsToEnd.end(), 1LL, [](long long acc, long long val) {
        return std::lcm(acc, val);
    });
    std::cout << res << '\n';
}