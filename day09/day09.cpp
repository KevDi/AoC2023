#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <numeric>
#include <sstream>
#include <vector>

int main() {
    std::ifstream data{"resources/data.txt"};
    long sum = 0;
    long sum_part_2 = 0;
    if (data.is_open()) {
        std::string line;
        while (std::getline(data, line)) {
            std::vector<long> tokens;

            std::string token;
            std::istringstream tokenStream(line);
            while (std::getline(tokenStream, token, ' ')) {
                tokens.push_back(std::stoi(token));
            }

            std::vector<long> res(tokens.size(), 0);
            std::vector<long> last_elements{tokens.back()};
            std::vector<long> first_elements{tokens.front()};

            std::adjacent_difference(tokens.begin(), tokens.end(), res.begin());
            res.erase(res.begin());
            last_elements.push_back(res.back());
            first_elements.push_back(res.front());

            while (!std::all_of(res.begin(), res.end(), [](int ele) { return ele == 0; })) {
                std::adjacent_difference(res.begin(), res.end(), res.begin());
                res.erase(res.begin());
                first_elements.push_back(res.front());
                last_elements.push_back(res.back());
            }

            sum += std::accumulate(last_elements.begin(), last_elements.end(), 0L);

            long first_element_res = 0L;

            for (size_t i = first_elements.size() - 1; i > 0; i--) {
                first_element_res = first_elements[i] - first_element_res;
            }

            sum_part_2 += first_elements[0] - first_element_res;
        }
    }
    std::cout << sum << '\n';
    std::cout << sum_part_2 << '\n';
}
