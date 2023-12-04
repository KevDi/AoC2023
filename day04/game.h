#pragma once
#include <string>

class Game
{
private:
    int id_{0};
public:
    Game(const std::string& game_line);
    ~Game() = default;

    int id() const;
};
