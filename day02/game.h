#pragma once
#include <string>
#include <unordered_map>

class Game {

public:
    Game(const std::string& game_string);

    int id() const;
    int blue() const;
    int green() const;
    int red() const;

private:

    int id_;
    std::unordered_map<std::string, int> val_{
        {"blue", 0},
        {"green", 0},
        {"red", 0}
    };
};