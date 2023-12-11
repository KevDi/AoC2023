#include "hand.h"

#include <iostream>
#include <regex>

std::unordered_map<char, int>
    Hand::card_value{
        {'1', 1},
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T', 10},
        {'J', 11},
        {'Q', 12},
        {'K', 13},
        {'A', 14}};

Hand::Hand(const std::string& line, bool part_2) {
    std::regex hand_reg{"(\\w+)\\s(\\d+)"};

    std::smatch matches;

    if (std::regex_match(line, matches, hand_reg)) {
        if (matches.size() != 3) {
            throw std::invalid_argument{"Wrong input!"};
        }
        bid_ = std::stoi(matches[2]);
        auto hand = matches[1].str();
        hand_ = hand;
        std::unordered_map<char, int> counts;

        for (char c : hand) {
            if (part_2 && c == 'J') {
                cards_.push_back(1);
            } else {
                cards_.push_back(card_value[c]);
            }
            counts[c]++;
        }

        if (part_2) {
            std::vector<std::pair<char, int>> count_vec{counts.begin(), counts.end()};
            std::sort(
                count_vec.begin(), count_vec.end(), [](const auto& a, const auto& b) {
                    return a.second > b.second;
                });
            set_type_part_2(count_vec, counts['J']);
        } else {
            std::vector<int> res;
            for (auto ele : counts) {
                res.push_back(ele.second);
            }

            std::sort(res.begin(), res.end(), std::greater<int>());
            set_type(res);
        }
    }
}

bool operator>(const Hand& lhs, const Hand& rhs) {
    if (lhs.type_ > rhs.type_) {
        return true;
    } else if (lhs.type_ == rhs.type_) {
        for (size_t i = 0; i < lhs.cards_.size(); i++) {
            if (lhs.cards_[i] > rhs.cards_[i]) {
                return true;
            } else if (lhs.cards_[i] < rhs.cards_[i]) {
                return false;
            }
        }
        return false;
    }
    return false;
}

bool operator<(const Hand& lhs, const Hand& rhs) {
    return rhs > lhs;
}

int Hand::bid() const {
    return bid_;
}

std::vector<int> Hand::cards() const {
    return cards_;
}

int Hand::type() const {
    return type_;
}

void Hand::set_type(const std::vector<int>& counts) {
    int top_ele = counts[0];
    switch (top_ele) {
        case 5:
        case 4:
            type_ = top_ele + 2;
            break;
        case 3:
            type_ = counts[1] == 2 ? top_ele + 2 : top_ele + 1;
            break;
        case 2:
            type_ = counts[1] == 2 ? top_ele + 1 : top_ele;
            break;
        default:
            type_ = 1;
            break;
    }
}

void Hand::set_type_part_2(const std::vector<std::pair<char, int>>& counts, int jokers) {
    auto top_ele = counts[0];
    switch (top_ele.second) {
        case 5:
            type_ = top_ele.second + 2;
            break;
        case 4:
            if (top_ele.first == 'J') {
                type_ = top_ele.second + 3;
            } else {
                type_ = jokers == 1 ? top_ele.second + 3 : top_ele.second + 2;
            }
            break;
        case 3:
            if (top_ele.first == 'J') {
                type_ = counts[1].second == 2 ? top_ele.second + 4 : top_ele.second + 3;
            } else {
                if (jokers == 2) {
                    type_ = top_ele.second + 4;
                } else if (jokers == 1) {
                    type_ = top_ele.second + 3;
                } else {
                    type_ = counts[1].second == 2 ? top_ele.second + 2 : top_ele.second + 1;
                }
            }
            break;
        case 2:
            if (top_ele.first == 'J') {
                type_ = counts[1].second == 2 ? top_ele.second + 4 : top_ele.second + 2;
            } else {
                if (jokers == 2) {
                    type_ = top_ele.second + 4;
                } else if (jokers == 1 && counts[1].second == 2) {
                    type_ = top_ele.second + 3;
                } else if (jokers == 1 && counts[1].second != 2) {
                    type_ = top_ele.second + 2;
                } else {
                    type_ = counts[1].second == 2 ? top_ele.second + 1 : top_ele.second;
                }
            }
            break;
        case 1:
            if (jokers == 1) {
                type_ = 2;
            } else {
                type_ = 1;
            }
            break;
        default:
            type_ = 1;
            break;
    }
}

std::string Hand::hand() const {
    return hand_;
}