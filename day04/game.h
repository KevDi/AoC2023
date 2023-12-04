#pragma once
#include <string>
#include <vector>

class Game
{
private:
    int id_{0};
    std::vector<int> winning_numbers_;
    std::vector<int> my_numbers_;

    void load_numbers(const std::string& number_line, std::vector<int>& result);
public:
    Game(const std::string& game_line);
    ~Game() = default;

    int id() const;
    int points() const;
    int matching() const;
    std::vector<int> winning_numbers() const;
    std::vector<int> my_numbers() const;
};
