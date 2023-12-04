#include <iostream>
#include <fstream>
#include <vector>
#include "engine.h"

int main() {
    std::ifstream data{"resources/data.txt"};
    std::vector<std::string> rows;
    if (data.is_open())
    {
        std::string line;
        while (std::getline(data, line))
        {
            rows.push_back(line);
        }
        data.close();
    }
    
    std::cout << get_number(rows) << '\n';
    std::cout << get_gear_number(rows) << '\n';
}