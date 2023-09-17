#pragma once
#include "gtest/gtest.h"
#include "../libant.h"

TEST(quadtree, test_quadtree_root_insert)
{
  quadtree qt;

  auto val = 20;
  qt.insert(0, 0, val);
  const auto root_value = qt.root->value;
  
  EXPECT_EQ(root_value, val);
}

TEST(quadtree, test_quadtree_child_insert)
{

  quadtree qt;
  qt.insert(0, 0, 0);
  const auto val = 21;
  qt.insert(1, 1, val);
  const auto child = qt.root->get_child(NE);

  ASSERT_NE(child, nullptr);
  ASSERT_EQ(child->value, val);
  
}


TEST(quadtree, test_quadtree_child_insert_non_leaf)
{

  quadtree qt;
  qt.insert(0, 0, 0);
  qt.insert(1, 1, 0);
  const auto val = 22;
  qt.insert(-1, 1, val);
  const auto first_insert = qt.root->get_child(NE);
  const auto second_insert = qt.root->get_child(NW);

  ASSERT_NE(first_insert, nullptr);
  EXPECT_EQ(first_insert->value, 0);
  
  ASSERT_NE(second_insert, nullptr);
  ASSERT_EQ(second_insert->value, val);
  
}

// test to ensure the result of qt.get is equivalent to manually retrieving node values as was done in previous test cases
TEST(quadtree, test_quadtree_get)
{

  quadtree qt;
  
  qt.insert(0, 0, 24);
  qt.insert(1, 1, 25);

  const auto root_node = qt.root;
  const auto child_node = qt.root->get_child(NE);

  const auto root_get = qt.get_value(0, 0);
  const auto child_get = qt.get_value(1, 1);
  
  EXPECT_EQ(root_node->value, root_get);
  EXPECT_EQ(child_node->value, child_get);

  // if (current_parent->is_leaf) case off child_node
  EXPECT_EQ(qt.get_value(2, 2), 0);
  // if (current_parent == nullptr) case off root_node
  EXPECT_EQ(qt.get_value(-1, 1), 0);
  
}

TEST(quadtree, test_quadtree_with_bounds)
{

  quadtree qt({5, 5});
  
  qt.insert(5, 5, 26);
  qt.insert(6, 7, 27);
  
  EXPECT_EQ(qt.get_value(10, 10), 26);
  EXPECT_EQ(qt.get_value(11, 12), 27);
  
}