#pragma once
#include <gtest/gtest.h>
#include "../libant.h"

TEST(la_matrix, test_la_matrix)
{
  // freshly initialized
  la_matrix t({ 10, 10 });
  EXPECT_EQ(t.get_value(0, 0), 0);

  // insert and get value
  t.insert(0, 0, 1);
  const auto val = t.get_value(0, 0);
  EXPECT_EQ(val, 1);

  // insert and get with bound-wrapping
  t.insert(-1, -1, 2);
  EXPECT_EQ(t.get_value(-1, -1), 2);
  EXPECT_EQ(t.get_value(9, 9), 2);

  t.insert(11, 11, 3);
  EXPECT_EQ(t.get_value(11, 11), 3);
  EXPECT_EQ(t.get_value(1, 1), 3);

  // test referential integrity
  auto& cell = t.get_cell(5, 5)->get();
  EXPECT_EQ(cell.value, 0);
  cell.value = 4;
  EXPECT_EQ(t.get_cell(5, 5)->get().value, 4);
  
}