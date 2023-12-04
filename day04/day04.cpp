#include <iostream>
#include <fstream>
#include <unordered_map>
#include "game.h"

int main() {
    std::ifstream data{"resources/data.txt"};
    int sum = 0;
    std::unordered_map<int, int> cards;
    if (data.is_open())
    {
        std::string line;
        while (std::getline(data, line))
        {
            Game game{line};
            sum += game.points();
            int matching = game.matching();
            
            cards[game.id()]++;
            if (matching > 0) {
                for(int j = 1; j <= cards[game.id()]; j++) {
                    for(int i = 1; i <= matching; i++) {
                        cards[game.id()+i]++;
                    }
                }
            }
        }
        data.close();
    }
    
    int ext_sum = 0;
    for(auto ele : cards) {
        ext_sum += ele.second;
    }

    std::cout << sum << '\n';
    std::cout << ext_sum << '\n';
}