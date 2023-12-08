#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Hand {
   public:
    Hand(const std::string& line, bool part_2 = false);

    int bid() const;
    std::vector<int> cards() const;
    int type() const;
    std::string hand() const;

    friend bool operator>(const Hand& lhs, const Hand& rhs);
    friend bool operator<(const Hand& lhs, const Hand& rhs);

   private:
    int bid_{0};
    std::vector<int> cards_{};
    int type_{0};
    std::string hand_{};

    void set_type(const std::vector<int>& counts);

    void set_type_part_2(const std::vector<std::pair<char, int>>& counts, int joker_count);

    static std::unordered_map<char, int> card_value;
};