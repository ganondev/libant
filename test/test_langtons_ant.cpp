#pragma once
#include <gtest/gtest.h>
#include "../libant.h"

TEST(langtons_ant, test_langtons_ant_quadtree)
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

  EXPECT_EQ(automaton.get_iteration(), 5);

}

TEST(langtons_ant, test_langtons_ant_bounded)
{

  quadtree qt({1, 1});
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

TEST(langtons_ant, test_langtons_ant_matrix)
{
  
  ant_automaton automaton(new la_matrix({3, 3}));
  
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
  // 2 instead of -1 due to toroidal projection
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
  // 2 instead of -1 due to toroidal projection
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