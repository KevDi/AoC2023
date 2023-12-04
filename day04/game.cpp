#include "game.h"
#include <regex>
#include <exception>

Game::Game(const std::string& game_line) {
    std::string tmp_line;
    std::regex id_reg{"Card\\s+(\\d+):"};

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

        load_numbers(winning_numbers, winning_numbers_);
        load_numbers(my_numbers, my_numbers_);
    }
}

int Game::id() const {
    return id_;
}

std::vector<int> Game::winning_numbers() const {
    return winning_numbers_;
}

std::vector<int> Game::my_numbers() const {
    return my_numbers_;
}

void Game::load_numbers(const std::string& number_line, std::vector<int>& result) {
    std::regex number_reg{"\\d+"};
    std::sregex_token_iterator words_begin(number_line.begin(), number_line.end(), number_reg);
    const std::sregex_token_iterator words_end;
    
    while(words_begin != words_end) {
        result.push_back(std::stoi(words_begin->str()));
        words_begin++;
    }
}

int Game::points() const {
    int counter = 0;
 
    for(auto& number : winning_numbers_) {
        if (std::find(my_numbers_.begin(), my_numbers_.end(), number) != my_numbers_.end()) {
            counter++;
        }
    }

    return counter != 0 ? 1 << (counter - 1) : 0;

}

int Game::matching() const {
    int counter = 0;
 
    for(auto& number : winning_numbers_) {
        if (std::find(my_numbers_.begin(), my_numbers_.end(), number) != my_numbers_.end()) {
            counter++;
        }
    }

    return counter;
}