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

    const std::regex blue_reg{"\\s(\\d+)\\sblue"};
    std::sregex_token_iterator words_begin(game_line.begin(), game_line.end(), blue_reg, 1);
    const std::sregex_token_iterator words_end;


    while(words_begin != words_end) {
        int tmp_blue = std::stoi(words_begin->str());
        if (tmp_blue > blue_) {
            blue_ = tmp_blue;
        }
        words_begin++;
    }

    const std::regex green_reg{"\\s(\\d+)\\sgreen"};
    std::sregex_token_iterator green_words_begin(game_line.begin(), game_line.end(), green_reg, 1);
    const std::sregex_token_iterator green_words_end;


    while(green_words_begin != green_words_end) {
        int tmp_green = std::stoi(green_words_begin->str());
        if (tmp_green > green_) {
            green_ = tmp_green;
        }
        green_words_begin++;
    }
}

int Game::id() const
{
    return id_;
}

int Game::blue() const
{
    return blue_;
}

int Game::green() const {
    return green_;
}