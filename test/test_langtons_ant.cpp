#pragma once
#include "gtest/gtest.h"
#include "../libant.h"

TEST(langtons_ant, test_langtons_ant)
{
  
  ant_automaton automaton(new quadtree());
  
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
  EXPECT_EQ(diff.x, -1);
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
  EXPECT_EQ(diff.x, -1);
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

}