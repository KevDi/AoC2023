#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <vector>

int main() {
    long groth = 1000000 - 1;
    std::ifstream data{"resources/data.txt"};
    std::vector<std::string> data_map;
    std::vector<std::pair<long, long>> galaxies;
    std::regex galaxy_reg{"#"};
    std::smatch match;
    long counter = 0L;
    if (data.is_open()) {
        std::string line;

        while (std::getline(data, line)) {
            std::sregex_token_iterator word_begin{line.begin(), line.end(), galaxy_reg};
            const std::sregex_token_iterator word_end;
            counter = word_begin == word_end ? counter + groth : counter;
            while (word_begin != word_end) {
                galaxies.push_back({counter, std::distance(line.cbegin(), word_begin->first)});
                word_begin++;
            }
            data_map.push_back(line);
            counter++;
        }
        counter = 0;
        for (auto i = 0; i < data_map[0].size(); i++) {
            bool empty = true;
            for (auto j = 0; j < data_map.size(); j++) {
                if (data_map[j][i] != '.') {
                    empty = false;
                    break;
                }
            }
            if (empty) {
                for (auto& galaxy : galaxies) {
                    if (galaxy.second >= (i + counter)) {
                        galaxy.second += groth;
                    }
                }
                counter += groth;
            }
        }

        data.close();
    }

    long long sum = 0;

    for (int i = 0; i < galaxies.size(); i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto dist = galaxies[j].first - galaxies[i].first + std::abs(galaxies[j].second - galaxies[i].second);
            sum += dist;
        }
    }

    std::cout << sum << '\n';
}