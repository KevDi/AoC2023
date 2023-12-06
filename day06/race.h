#pragma once
#include <vector>

struct Race {
    int time{0};
    int record{0};

    std::vector<int> winning_distances() const;
};