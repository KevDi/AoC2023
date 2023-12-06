#include <gmock/gmock.h>
#include "race.h"

using namespace testing;

TEST(Day06, GetWinningDistancesReturnsAllThePossibleDistances) {
    Race race;
    race.time = 7;
    race.record = 9;

    std::vector<int> expected{10,12,12,10};

    ASSERT_THAT(race.winning_distances(), Eq(expected));
}