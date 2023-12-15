#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

struct Lens {
    std::string label{};
    int length{0};

    int hash_func() {
        int curr_val = 0;
        for (auto& ch : label) {
            auto ascii_val = static_cast<int>(ch);
            curr_val += ascii_val;
            curr_val *= 17;
            curr_val %= 256;
        }
        return curr_val;
    }
};

int main() {
    std::ifstream data{"resources/data.txt"};
    int sum = 0;
    bool part2 = true;
    std::unordered_map<std::string, int> cache;
    std::unordered_map<int, std::vector<Lens>> boxes;
    boxes.reserve(256);
    if (data.is_open()) {
        std::string line;
        std::getline(data, line);
        std::istringstream tokenStream(line);
        std::string token;

        while (std::getline(tokenStream, token, ',')) {
            if (!part2) {
                if (auto it = cache.find(token); it != cache.end()) {
                    std::cout << "Cache hit\n";
                    sum += it->second;
                } else {
                    int curr_val = 0;
                    for (auto& ch : token) {
                        auto ascii_val = static_cast<int>(ch);
                        curr_val += ascii_val;
                        curr_val *= 17;
                        curr_val %= 256;
                    }
                    sum += curr_val;
                    cache[token] = curr_val;
                }
            } else {
                if (auto it = token.find('='); it != std::string::npos) {
                    Lens curr_lens{token.substr(0, it), std::stoi(token.substr(it + 1, token.size()))};
                    auto& curr_box = boxes[curr_lens.hash_func()];
                    auto iter = std::find_if(curr_box.begin(), curr_box.end(), [&curr_lens](const Lens& lens) {
                        return lens.label == curr_lens.label;
                    });
                    if (iter != curr_box.end()) {
                        iter->length = curr_lens.length;
                    } else {
                        curr_box.push_back(curr_lens);
                    }
                } else if (auto it = token.find('-'); it != std::string::npos) {
                    Lens curr_lens{token.substr(0, it), 0};
                    auto& curr_box = boxes[curr_lens.hash_func()];
                    auto iter = std::find_if(curr_box.begin(), curr_box.end(), [&curr_lens](const Lens& lens) {
                        return lens.label == curr_lens.label;
                    });

                    if (iter != curr_box.end()) {
                        curr_box.erase(iter);
                    }
                }
            }
        }
        data.close();
    }
    if (part2) {
        for (auto& pair : boxes) {
            for (int i = 0; i < pair.second.size(); i++) {
                int curr_val = pair.first + 1;
                curr_val *= i + 1;
                curr_val *= pair.second[i].length;
                sum += curr_val;
            }
        }
    }

    std::cout << sum << '\n';

    return 0;
}