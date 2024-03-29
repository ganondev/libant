﻿#pragma once

#include "fixtures.h"
#include "../libant.h"

class LangtonsAntTest : public AutomatonTestFixtures {
  // No need for additional setup and teardown here
};

INSTANTIATE_TEST_CASE_P(
    BackendTypes,
    LangtonsAntTest,
    ::testing::ValuesIn(LangtonsAntTest::shared_params()),
    custom_test_name<LangtonsAntTest>
);

// TEST_P(LangtonsAntTest, test_langtons_ant_quadtree)
TEST_P(LangtonsAntTest, test_langtons_ant)
{
  auto backend = get_backend({3, 3});
  ant_automaton automaton{backend.get()};
  
  auto ant = automaton.add_ant<langtons_ant>();

  // initially facing "north"
  
  EXPECT_EQ(automaton.get_value(0, 0), 0);
  EXPECT_EQ(ant->position[0], 0);
  EXPECT_EQ(ant->position[1], 0);
  EXPECT_EQ(ant->orientation, 0);
  
  auto diffs = automaton.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(automaton.get_value(0, 0)));
  EXPECT_EQ(ant->position[0], -1);
  EXPECT_EQ(ant->position[1], 0);
  EXPECT_EQ(ant->orientation, 3);
  auto diff = diffs[0];
  EXPECT_EQ(diff.x, 0);
  EXPECT_EQ(diff.y, 0);
  EXPECT_EQ(diff.old_value, 0);
  EXPECT_EQ(diff.new_value, 1);

  diffs = automaton.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(automaton.get_value(-1, 0)));
  EXPECT_EQ(ant->position[0], -1);
  EXPECT_EQ(ant->position[1], 1);
  EXPECT_EQ(ant->orientation, 2);
  diff = diffs[0];
  EXPECT_EQ(diff.x, 2);
  EXPECT_EQ(diff.y, 0);
  EXPECT_EQ(diff.old_value, 0);
  EXPECT_EQ(diff.new_value, 1);

  diffs = automaton.tick();

  // left turn and move forward
  

  EXPECT_TRUE(static_cast<bool>(automaton.get_value(-1, 1)));
  EXPECT_EQ(ant->position[0], 0);
  EXPECT_EQ(ant->position[1], 1);
  EXPECT_EQ(ant->orientation, 1);
  diff = diffs[0];
  EXPECT_EQ(diff.x, 2);
  EXPECT_EQ(diff.y, 1);
  EXPECT_EQ(diff.old_value, 0);
  EXPECT_EQ(diff.new_value, 1);

  diffs = automaton.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(automaton.get_value(0, 1)));
  EXPECT_EQ(ant->position[0], 0);
  EXPECT_EQ(ant->position[1], 0);
  EXPECT_EQ(ant->orientation, 0);
  diff = diffs[0];
  EXPECT_EQ(diff.x, 0);
  EXPECT_EQ(diff.y, 1);
  EXPECT_EQ(diff.old_value, 0);
  EXPECT_EQ(diff.new_value, 1);

  diffs = automaton.tick();

  // right turn and move forward, detoggling the first cell

  EXPECT_FALSE(static_cast<bool>(automaton.get_value(0, 0)));
  EXPECT_EQ(ant->position[0], 1);
  EXPECT_EQ(ant->position[1], 0);
  EXPECT_EQ(ant->orientation, 1);
  diff = diffs[0];
  EXPECT_EQ(diff.x, 0);
  EXPECT_EQ(diff.y, 0);
  EXPECT_EQ(diff.old_value, 1);
  EXPECT_EQ(diff.new_value, 0);

  EXPECT_EQ(automaton.get_iteration(), 5);

}

TEST(langtons_ant, test_langtons_ant_bounded)
{

  la_quadtree qt({1, 1});
  ant_automaton automaton(&qt);
  automaton.add_ant<langtons_ant>();

  // ant orientation and position will 'change', but the diff should always report a change at 0, 0
  
  auto diffs = automaton.tick();
  auto diff = diffs[0];
  EXPECT_EQ(diff.x, 0);
  EXPECT_EQ(diff.y, 0);
  EXPECT_EQ(diff.old_value, 0);
  EXPECT_EQ(diff.new_value, 1);
  // node value should match diff
  EXPECT_EQ(qt.root->value, 1);

  diffs = automaton.tick();
  diff = diffs[0];
  EXPECT_EQ(diff.x, 0);
  EXPECT_EQ(diff.y, 0);
  EXPECT_EQ(diff.old_value, 1);
  EXPECT_EQ(diff.new_value, 0);
  EXPECT_EQ(qt.root->value, 0);
  // node shouldn't have any children
  EXPECT_EQ(qt.root->get_child_count(), 0);
  
}