#include <iostream>
#include <fstream>

int main() {
    std::ifstream data{"resources/data.txt"};
    int sum = 0;
    if (data.is_open())
    {
        std::string line;
        while (std::getline(data, line))
        {
            
        }
        data.close();
    }

}