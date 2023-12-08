#include <gmock/gmock.h>

#include "hand.h"

using namespace testing;

TEST(Day07, HandSetsBid) {
    Hand hand{"32T3K 765"};

    ASSERT_THAT(hand.bid(), Eq(765));
}

TEST(Day07, SplitHandIntoSingleElements) {
    Hand hand{"32T3K 765"};
    Hand hand_2{"8JQAT 64"};
    std::vector<int> expected{3, 2, 10, 3, 13};
    std::vector<int> expected_2{8, 11, 12, 14, 10};
    ASSERT_THAT(hand.cards(), Eq(expected));
    ASSERT_THAT(hand_2.cards(), Eq(expected_2));
}

TEST(Day07, HandSetsTypeBasedOnInput) {
    Hand hand{"23456 765"};
    Hand hand_2{"A23A4 765"};
    Hand hand_3{"23432 765"};
    Hand hand_4{"TTT98 765"};
    Hand hand_5{"23332 765"};
    Hand hand_6{"AA8AA 765"};
    Hand hand_7{"AAAAA 765"};
    Hand hand_8{"JJ36K 969", true};
    Hand hand_9{"2JJ25 296", true};

    ASSERT_THAT(hand.type(), Eq(1));
    ASSERT_THAT(hand_2.type(), Eq(2));
    ASSERT_THAT(hand_3.type(), Eq(3));
    ASSERT_THAT(hand_4.type(), Eq(4));
    ASSERT_THAT(hand_5.type(), Eq(5));
    ASSERT_THAT(hand_6.type(), Eq(6));
    ASSERT_THAT(hand_7.type(), Eq(7));
    ASSERT_THAT(hand_8.type(), Eq(4));
    ASSERT_THAT(hand_9.type(), Eq(6));
}

TEST(Day07, HandsCouldBeCompared) {
    Hand hand_1{"AA8AA 765"};
    Hand hand_2{"AAAAA 765"};

    ASSERT_TRUE(hand_2 > hand_1);
}

TEST(Day07, HandsComparedByHighestCardIfSameType) {
    Hand hand_2{"AAAAA 765"};
    Hand hand_1{"KKKKK 123"};

    Hand hand_3{"KK677 28"};
    Hand hand_4{"KTJJT 220"};

    ASSERT_TRUE(hand_2 > hand_1);
    ASSERT_TRUE(hand_4 < hand_3);
}