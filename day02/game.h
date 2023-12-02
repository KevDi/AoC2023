#pragma once
#include <string>

class Game {

public:
    Game(const std::string& game_string);

    int id() const;
    int blue() const;

private:

    int id_;
    //int red_{0};
    //int green_{0};
    int blue_{0};
};