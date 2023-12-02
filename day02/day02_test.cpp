#include <gmock/gmock.h>
#include "game.h"

using namespace testing;

TEST(Day02, GameSetsID) {
    Game game{"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"};
    Game game_2{"Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"};

    ASSERT_THAT(game.id(), Eq(1));
    ASSERT_THAT(game_2.id(), Eq(5));
}

TEST(Day02, GameSetsBlue) {
    Game game{"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"};
    Game game_2{"Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"};

    ASSERT_THAT(game.blue(), Eq(6));
    ASSERT_THAT(game_2.blue(), Eq(2));
}