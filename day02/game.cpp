#include "game.h"
#include <regex>
#include <iostream>

Game::Game(const std::string &game_line)
{

    std::regex id_reg{"Game\\s(\\d+).*"};

    std::smatch matches;

    if (std::regex_match(game_line, matches, id_reg))
    {

        if (matches.size() == 2)
        {
            std::cerr << matches[1].str() << '\n';
            id_ = std::stoi(matches[1].str());
        }
    }

    const std::regex blue_reg{"\\s(\\d+)\\s(blue|green|red)"};
    int submatches[] = { 2, 1 };
    std::sregex_token_iterator words_begin(game_line.begin(), game_line.end(), blue_reg, submatches);
    const std::sregex_token_iterator words_end;


    while(words_begin != words_end) {
        auto tmp_key = words_begin->str();
        int tmp_val = std::stoi((++words_begin)->str());
        if (tmp_val > val_[tmp_key]) {
            val_[tmp_key] = tmp_val;
        }
        words_begin++;
    }
}

int Game::id() const
{
    return id_;
}

int Game::blue() const
{
    return val_.at("blue");
}

int Game::green() const {
    return val_.at("green");
}

int Game::red() const {
    return val_.at("red");
}