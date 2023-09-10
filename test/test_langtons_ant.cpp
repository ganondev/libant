#include "gtest/gtest.h"
#include "../libant.h"

TEST(langtons_ant, test_langtons_ant)
{

  quadtree qt;
  langtons_ant ant;
  qt.add_ant(ant);

  // initially facing "north"
  
  EXPECT_EQ(qt.get_value(0, 0), nullptr);
  EXPECT_EQ(ant.position[0], 0);
  EXPECT_EQ(ant.position[1], 0);
  EXPECT_EQ(ant.orientation, 0);
  
  qt.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(qt.get_value(0, 0)));
  EXPECT_EQ(ant.position[0], -1);
  EXPECT_EQ(ant.position[1], 0);
  EXPECT_EQ(ant.orientation, 3);

  qt.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(qt.get_value(-1, 0)));
  EXPECT_EQ(ant.position[0], -1);
  EXPECT_EQ(ant.position[1], 1);
  EXPECT_EQ(ant.orientation, 2);

  qt.tick();

  // left turn and move forward
  

  EXPECT_TRUE(static_cast<bool>(qt.get_value(-1, 1)));
  EXPECT_EQ(ant.position[0], 0);
  EXPECT_EQ(ant.position[1], 1);
  EXPECT_EQ(ant.orientation, 1);

  qt.tick();

  // left turn and move forward

  EXPECT_TRUE(static_cast<bool>(qt.get_value(0, 1)));
  EXPECT_EQ(ant.position[0], 0);
  EXPECT_EQ(ant.position[1], 0);
  EXPECT_EQ(ant.orientation, 0);

  qt.tick();

  // right turn and move forward, detoggling the first cell

  EXPECT_FALSE(static_cast<bool>(qt.get_value(0, 0)));
  EXPECT_EQ(ant.position[0], 1);
  EXPECT_EQ(ant.position[1], 0);
  EXPECT_EQ(ant.orientation, 1);

}