#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

bool has_smudge(std::string& left, std::string& right) {
    int change_counter = 0;
    int change_idx;
    for (int i = 0; i < left.size(); i++) {
        if (left[i] != right[i]) {
            change_idx = i;
            change_counter++;
        }
        if (change_counter > 1) {
            return false;
        }
    }
    if (change_counter == 1) {
        left[change_idx] = right[change_idx];
        return true;
    }
    return false;
}

bool is_mirror(std::vector<std::string> data, int start, bool smudge) {
    for (int j = 0; j <= start; j++) {
        if ((start + 1 + j) >= data.size()) {
            return smudge;
        }

        if (smudge) {
            if (data[start - j] != data[start + 1 + j]) {
                return false;
            }
        } else {
            if (data[start - j] != data[start + 1 + j]) {
                smudge = has_smudge(data[start - j], data[start + 1 + j]);
                if (!smudge) {
                    return false;
                }
            }
        }
    }
    return smudge;
}

int analyse_data(std::vector<std::string>& data) {
    std::vector<int> possible_smudge;
    bool smudge = false;
    for (int i = 0; i < data.size() - 1; i++) {
        std::string old_data_one = data[i];
        std::string old_data_two = data[i + 1];
        smudge = has_smudge(data[i], data[i + 1]);
        if (smudge) {
            if (is_mirror(data, i, true)) {
                return i + 1;
            }
            data[i] = old_data_one;
            data[i + 1] = old_data_two;
        } else if (data[i] == data[i + 1]) {
            possible_smudge.push_back(i);
        }
    }
    if (!smudge && !possible_smudge.empty()) {
        for (auto ele = possible_smudge.rbegin(); ele != possible_smudge.rend(); ele++) {
            if (is_mirror(data, *ele, false)) {
                return *ele + 1;
            }
        }
    }

    return 0;
}

int main() {
    std::ifstream data{"resources/data.txt"};
    int sum = 0;
    if (data.is_open()) {
        std::string line;
        std::vector<std::string> raw_data;
        std::vector<std::string> column_data;
        while (std::getline(data, line)) {
            if (line.empty()) {
                int row_count = analyse_data(raw_data);
                sum += 100 * row_count;
                sum += (row_count > 0 ? 0 : analyse_data(column_data));
                raw_data.clear();
                column_data.clear();
                continue;
            } else if (data.eof()) {
                raw_data.push_back(line);
                for (auto i = 0; i < line.size(); i++) {
                    column_data[i].push_back(line[i]);
                }
                int row_count = analyse_data(raw_data);
                sum += 100 * row_count;
                sum += (row_count > 0 ? 0 : analyse_data(column_data));
            } else {
                if (column_data.empty()) {
                    for (auto ele : line) {
                        column_data.push_back({ele});
                    }
                } else {
                    for (auto i = 0; i < line.size(); i++) {
                        column_data[i].push_back(line[i]);
                    }
                }

                raw_data.push_back(line);
            }
        }
    }

    data.close();
    std::cout << sum << '\n';
}
