#include "game.h"
#include <regex>
#include <exception>

Game::Game(const std::string& game_line) {
    std::string tmp_line;
    std::regex id_reg{"Card\\s(\\d+):"};

    std::smatch matches;

    if (std::regex_search(game_line, matches, id_reg))
    {
        if (matches.size() == 2)
        {
            id_ = std::stoi(matches[1].str());
            tmp_line = matches.suffix();
        }
    }

    if(tmp_line.empty()) {
        throw std::invalid_argument{"Wrong format"};
    }

    auto splitter = tmp_line.find('|');
    if (splitter != std::string::npos) {
        auto winning_numbers = tmp_line.substr(0, splitter);
        auto my_numbers = tmp_line.substr(splitter + 1, tmp_line.length());
        return;
    }
}

int Game::id() const {
    return id_;
}