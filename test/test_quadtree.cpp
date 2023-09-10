#include "gtest/gtest.h"
#include "../quadtree/quadtree.h"

TEST(quadtree, test_quadtree_root_insert)
{
  quadtree qt;

  const char* val = "test";
  qt.insert(0, 0, const_cast<char*>(val));
  const auto root_value = static_cast<const char*>(qt.root->value);
  
  EXPECT_EQ(root_value, val);
}

TEST(quadtree, test_quadtree_child_insert)
{

  quadtree qt;
  qt.insert(0, 0, nullptr);
  const char* val = "test";
  qt.insert(1, 1, const_cast<char*>(val));
  const auto child = qt.root->children[NE];

  ASSERT_NE(child, nullptr);
  ASSERT_EQ(child->value, val);
  
}


TEST(quadtree, test_quadtree_child_insert_non_leaf)
{

  quadtree qt;
  qt.insert(0, 0, nullptr);
  qt.insert(1, 1, nullptr);
  const char* val = "test";
  qt.insert(-1, 1, const_cast<char*>(val));
  const auto first_insert = qt.root->children[NE];
  const auto second_insert = qt.root->children[NW];

  ASSERT_NE(first_insert, nullptr);
  EXPECT_EQ(first_insert->value, nullptr);
  
  ASSERT_NE(second_insert, nullptr);
  ASSERT_EQ(second_insert->value, val);
  
}

// test to ensure the result of qt.get is equivalent to manually retrieving node values as was done in previous test cases
TEST(quadtree, test_quadtree_get)
{

  quadtree qt;

  const char* root_val = "root";
  const char* child_val = "child";
  
  qt.insert(0, 0, const_cast<char*>(root_val));
  qt.insert(1, 1, const_cast<char*>(child_val));

  const auto root_node = qt.root;
  const auto child_node = qt.root->children[NE];

  const auto root_get = qt.get_value(0, 0);
  const auto child_get = qt.get_value(1, 1);
  
  EXPECT_EQ(root_node->value, root_get);
  EXPECT_EQ(child_node->value, child_get);

  // if (current_parent->is_leaf) case off child_node
  EXPECT_EQ(qt.get_value(2, 2), nullptr);
  // if (current_parent == nullptr) case off root_node
  EXPECT_EQ(qt.get_value(-1, 1), nullptr);
  
}