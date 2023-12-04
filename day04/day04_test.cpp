#include <gmock/gmock.h>
#include "game.h"

using namespace testing;

TEST(Day04, GameIDIsSet) {
    Game game{"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"};

    ASSERT_THAT(game.id(), Eq(1));
}

TEST(Day04, GameSetsWinningNumbers) {
    Game game{"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"};
    std::vector<int> expected{41,48,83,86,17};

    ASSERT_THAT(game.winning_numbers(), Eq(expected));
}

TEST(Day04, GameSetsMyNumbers) {
    Game game{"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"};
    std::vector<int> expected{83,86, 6, 31, 17, 9, 48, 53};

    ASSERT_THAT(game.my_numbers(), Eq(expected));
}

TEST(Day04, GameReturnsPoints) {
    Game game{"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"};
    
    ASSERT_THAT(game.points(), Eq(8));
}