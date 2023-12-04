#include <gmock/gmock.h>
#include "game.h"

using namespace testing;

TEST(Day04, GameIDIsSet) {
    Game game{"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"};

    ASSERT_THAT(game.id(), Eq(1));
}