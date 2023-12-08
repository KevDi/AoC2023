#include <algorithm>
#include <fstream>
#include <iostream>

#include "hand.h"

int main() {
    std::ifstream data{"resources/data.txt"};
    long long sum = 0;
    std::vector<Hand> hands;
    if (data.is_open()) {
        std::string line;

        while (std::getline(data, line)) {
            hands.emplace_back(line, true);
        }

        data.close();
    }
    std::sort(hands.begin(), hands.end());

    int counter = 1;
    for (auto& ele : hands) {
        // std::cout << "('" << ele.hand() << "', '" << ele.bid() << "')"
        //           << ":" << ele.type() << '\n';
        sum += (ele.bid() * counter++);
    }

    std::cout << sum << '\n';
}