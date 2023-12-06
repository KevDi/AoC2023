#include "race.h"

std::vector<int> Race::winning_distances() const {
    std::vector<int> result;

    for(int i = 0; i <= time; i++) {
        int distance = i * (time -i);
        if(distance > record) {
            result.push_back(distance);
        }
    }
    return result;
}