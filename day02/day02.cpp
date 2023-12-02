#include <iostream>
#include <fstream>
#include "game.h"

int main() {
    std::ifstream data{"resources/data.txt"};
    int sum = 0;
    int power_sum = 0;
    if (data.is_open())
    {
        std::string line;
        while (std::getline(data, line))
        {
            Game game{line};
            power_sum += game.power();
            if (game.is_valid(12,13,14)) {
                sum += game.id();
            }
        }
        data.close();
    }
    
    std::cout << sum << '\n';
    std::cout << power_sum << '\n';
}

