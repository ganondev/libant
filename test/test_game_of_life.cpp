#pragma once

#include "fixtures.h"

class GameOfLifeTest : public AutomatonTestFixtures {
  // No need for additional setup and teardown here
};

INSTANTIATE_TEST_CASE_P(
    BackendTypes,
    GameOfLifeTest,
    ::testing::ValuesIn(GameOfLifeTest::shared_params()),
    custom_test_name<GameOfLifeTest>
);

TEST_P(GameOfLifeTest, test_toggle)
{
  const auto backend = get_backend({1, 1});
  la_game_of_life automaton{backend.get()};
  EXPECT_EQ(automaton.get_value(0, 0), 0);
  automaton.toggle_cell(0, 0);
  EXPECT_EQ(automaton.get_value(0, 0), 1);
  automaton.toggle_cell(0, 0);
  EXPECT_EQ(automaton.get_value(0, 0), 0);
}

TEST_P(GameOfLifeTest, test_empty_state)
{
  const auto backend = get_backend({3, 3});
  la_game_of_life automaton(backend.get());
  EXPECT_EQ(automaton.get_value(0, 0), 0);
  auto diffs = automaton.tick();
  EXPECT_EQ(diffs.size(), 0);
}

TEST_P(GameOfLifeTest, test_cell_birth)
{

  const auto backend = get_backend({3, 3});
  la_game_of_life automaton(backend.get());

  automaton.toggle_cell(0, 0);
  automaton.toggle_cell(1, 0);
  automaton.toggle_cell(2, 2);

  // |.||.
  // .##X|
  // |X##.
  // |X##.
  // .||.|

  // expect center is empty
  EXPECT_EQ(automaton.get_value(1, 1), 0);

  const auto diffs = automaton.tick();

  // XXX
  // XXX
  // XXX

  // expect 6 changes
  EXPECT_EQ(diffs.size(), 6);

  // all changes should report a change from 0 -> 1
  for (auto [x, y, old_value, new_value] : diffs)
  {
    EXPECT_EQ(old_value, 0);
    EXPECT_EQ(new_value, 1);
  }

  // all cells should now be alive
  for (int64_t x = 0; x < 3; x++)
  {
    for (int64_t y = 0; y < 3; y++)
    {
      EXPECT_EQ(automaton.get_value(x, y), 1);
    }
  }
  
}

TEST_P(GameOfLifeTest, test_cell_death_by_loneliness)
{

  auto backend = get_backend({3, 3});
  la_game_of_life automaton(backend.get());

  automaton.toggle_cell(1, 1);

  // ###
  // #X#
  // ###

  // expect center is alive
  EXPECT_EQ(automaton.get_value(1, 1), 1);

  auto diffs = automaton.tick();

  // ###
  // ###
  // ###

  // expect 1 change
  EXPECT_EQ(diffs.size(), 1);

  // change should report a change from 1 -> 0 at center
  auto diff = diffs[0];
  EXPECT_EQ(diff.old_value, 1);
  EXPECT_EQ(diff.new_value, 0);
  EXPECT_EQ(diff.x, 1);
  EXPECT_EQ(diff.y, 1);

  // all cells should now be dead
  for (int64_t x = 0; x < 3; x++)
  {
    for (int64_t y = 0; y < 3; y++)
    {
      EXPECT_EQ(automaton.get_value(x, y), 0);
    }
  }

  // Do it again, but there is another live cell to the left of center
  backend = get_backend({3, 3});
  automaton = la_game_of_life(backend.get());

  automaton.toggle_cell(1, 1);
  automaton.toggle_cell(0, 1);

  // ###
  // XX#
  // ###

  // expect center and left are alive
  EXPECT_EQ(automaton.get_value(1, 1), 1);
  EXPECT_EQ(automaton.get_value(0, 1), 1);

  diffs = automaton.tick();

  // ###
  // ###
  // ###

  // expect 2 changes
  EXPECT_EQ(diffs.size(), 2);

  // change should report a change from 1 -> 0 at center and mid-left
  diff = diffs[0];
  EXPECT_EQ(diff.old_value, 1);
  EXPECT_EQ(diff.new_value, 0);
  EXPECT_EQ(diff.x, 0);
  EXPECT_EQ(diff.y, 1);
  diff = diffs[1];
  EXPECT_EQ(diff.old_value, 1);
  EXPECT_EQ(diff.new_value, 0);
  EXPECT_EQ(diff.x, 1);
  EXPECT_EQ(diff.y, 1);
  
  // all cells should now be dead
  for (int64_t x = 0; x < 3; x++)
  {
    for (int64_t y = 0; y < 3; y++)
    {
      EXPECT_EQ(automaton.get_value(x, y), 0);
    }
  }
  
}

TEST_P(GameOfLifeTest, test_death_by_overpopulation)
{

  auto backend = get_backend({3, 3});
  la_game_of_life automaton(backend.get());

  automaton.toggle_cell(0, 0);
  automaton.toggle_cell(1, 0);
  automaton.toggle_cell(2, 0);
  automaton.toggle_cell(0, 1);
  automaton.toggle_cell(1, 1);
  automaton.toggle_cell(2, 1);
  automaton.toggle_cell(0, 2);
  automaton.toggle_cell(1, 2);
  automaton.toggle_cell(2, 2);

  // make sure all values are 1
  for (int64_t x = 0; x < 3; x++)
  {
    for (int64_t y = 0; y < 3; y++)
    {
      EXPECT_EQ(automaton.get_value(x, y), 1);
    }
  }
  
  auto diffs = automaton.tick();
  
  EXPECT_EQ(diffs.size(), 9);

  // check that all the diffs show a transition from 1 -> 0
  for (auto [x, y, old_value, new_value] : diffs)
  {
    EXPECT_EQ(old_value, 1);
    EXPECT_EQ(new_value, 0);
  }

  // all the active cells should have died
  for (int64_t x = 0; x < 3; x++)
  {
    for (int64_t y = 0; y < 3; y++)
    {
      EXPECT_EQ(automaton.get_value(x, y), 0);
    }
  }

  // ticking again should have no effect, yielding an empty diff list
  diffs = automaton.tick();
  EXPECT_EQ(diffs.size(), 0);

}

TEST_P(GameOfLifeTest, test_game_of_life_cell_sustaining)
{
  const auto backend = get_backend({4, 4});
  la_game_of_life automaton(backend.get());

  automaton.toggle_cell(1, 1);
  automaton.toggle_cell(1, 2);
  automaton.toggle_cell(2, 1);
  automaton.toggle_cell(2, 2);

  // ####
  // #XX#
  // #XX#
  // ####

  // expect center cells to be alive
  EXPECT_EQ(automaton.get_value(1, 1), 1);
  EXPECT_EQ(automaton.get_value(1, 2), 1);
  EXPECT_EQ(automaton.get_value(2, 1), 1);
  EXPECT_EQ(automaton.get_value(2, 2), 1);

  const auto diff = automaton.tick();

  // ####
  // #XX#
  // #XX#
  // ####

  // expect no changes
  EXPECT_EQ(diff.size(), 0);

  // center cells should still be alive
  EXPECT_EQ(automaton.get_value(1, 1), 1);
  EXPECT_EQ(automaton.get_value(1, 2), 1);
  EXPECT_EQ(automaton.get_value(2, 1), 1);
  EXPECT_EQ(automaton.get_value(2, 2), 1);
  
}