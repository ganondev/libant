#pragma once
#include "gtest/gtest.h"
#include "../libant.h"

TEST(langtons_ant, test_langtons_ant)
{
  
  ant_automaton automaton(new quadtree());
  
  langtons_ant ant;
  automaton.add_ant(&ant);

  // initially facing "north"
  
  EXPECT_EQ(automaton.get_value(0, 0), 0);
  EXPECT_EQ(ant.position[0], 0);
  EXPECT_EQ(ant.position[1], 0);
  EXPECT_EQ(ant.orientation, 0);
  
  automaton.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(automaton.get_value(0, 0)));
  EXPECT_EQ(ant.position[0], -1);
  EXPECT_EQ(ant.position[1], 0);
  EXPECT_EQ(ant.orientation, 3);

  automaton.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(automaton.get_value(-1, 0)));
  EXPECT_EQ(ant.position[0], -1);
  EXPECT_EQ(ant.position[1], 1);
  EXPECT_EQ(ant.orientation, 2);

  automaton.tick();

  // left turn and move forward
  

  EXPECT_TRUE(static_cast<bool>(automaton.get_value(-1, 1)));
  EXPECT_EQ(ant.position[0], 0);
  EXPECT_EQ(ant.position[1], 1);
  EXPECT_EQ(ant.orientation, 1);

  automaton.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(automaton.get_value(0, 1)));
  EXPECT_EQ(ant.position[0], 0);
  EXPECT_EQ(ant.position[1], 0);
  EXPECT_EQ(ant.orientation, 0);

  automaton.tick();

  // right turn and move forward, detoggling the first cell

  EXPECT_FALSE(static_cast<bool>(automaton.get_value(0, 0)));
  EXPECT_EQ(ant.position[0], 1);
  EXPECT_EQ(ant.position[1], 0);
  EXPECT_EQ(ant.orientation, 1);

}