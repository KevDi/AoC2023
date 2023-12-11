#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <vector>

int main() {
    std::ifstream data{"resources/data.txt"};
    std::vector<std::string> data_map;
    std::vector<std::pair<int, int>> galaxies;
    std::regex galaxy_reg{"#"};
    std::smatch match;
    int counter = 0;
    if (data.is_open()) {
        std::string line;

        while (std::getline(data, line)) {
            std::sregex_token_iterator word_begin{line.begin(), line.end(), galaxy_reg};
            const std::sregex_token_iterator word_end;
            while (word_begin != word_end) {
                galaxies.push_back({counter, std::distance(line.begin(), word_begin->first)});
                word_begin++;
            }
            data_map.push_back(line);
        }

        // for (auto i = 0; i < data_map[0].size(); i++) {
        //     for (auto j = 0; j < data_map.size(); j++) {
        //         if (data_map[j][i] != '.') {
        //             break;
        //         }
        //     }
        // }

        data.close();
    }
}