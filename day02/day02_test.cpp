#include <gmock/gmock.h>
#include "game.h"

using namespace testing;

const std::string GAME_ONE_LINE{"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"};
const std::string GAME_TWO_LINE{"Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"};

TEST(Day02, GameSetsID) {
    Game game{GAME_ONE_LINE};
    Game game_2{GAME_TWO_LINE};

    ASSERT_THAT(game.id(), Eq(1));
    ASSERT_THAT(game_2.id(), Eq(5));
}

TEST(Day02, GameSetsBlue) {
    Game game{GAME_ONE_LINE};
    Game game_2{GAME_TWO_LINE};

    ASSERT_THAT(game.blue(), Eq(6));
    ASSERT_THAT(game_2.blue(), Eq(2));
}

TEST(Day02, GameSetsGreen) {
    Game game{GAME_ONE_LINE};
    Game game_2{GAME_TWO_LINE};

    ASSERT_THAT(game.green(), Eq(2));
    ASSERT_THAT(game_2.green(), Eq(3));
}

TEST(Day02, GameSetsRed) {
    Game game{GAME_ONE_LINE};

    ASSERT_THAT(game.red(), Eq(4));
}