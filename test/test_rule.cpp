#include <gtest/gtest.h>

#include "fixtures.h"
#include "../libant.h"

using namespace libant;

TEST(rule, test_rule_mapper) {
    
    rule r;

    ASSERT_EQ(r.mapper, nullptr); // Mapper should be zeroed
    
    r.maps_to([](const symbols&) {
        return 1;
    });

    ASSERT_NE(r.mapper, nullptr);  // Assert that mapper is set
    ASSERT_EQ(r.apply({{}}), 1);  // Assert that apply returns the expected result using the variable value
    
}

TEST(rule, test_rule_mapper_with_variable_cell) {
    
    rule r;
    r.maps_to([](const symbols& vars) {
        
        // vars should be congruent with the assignments vector
        EXPECT_EQ(vars.table.size(), 1);
        EXPECT_TRUE(vars.table.contains('a'));
        EXPECT_EQ(vars.value_of('a'), 1);
        
        return vars.value_of('a') + 1;
        
    });
    
    const std::vector<std::vector<int>> slice{{1}};
    r.variable_cell({0, 0}, 'a');

    ASSERT_EQ(r.assignments.size(), 1);  // Assert vector is populated
    ASSERT_EQ(r.assignments[0].variable_name, 'a');  // Assert correct symbol
    ASSERT_EQ(r.apply(slice), 2);  // Assert that apply returns the expected result using the variable value
    
}

TEST(rule, test_rule_mapper_invalid_variable)
{
    
    const std::function predicate = [](const symbols& vars) {
        EXPECT_EQ(vars.table.size(), 0);
        return vars.value_of('a') + 1; // should throw here
    };
    EXPECT_THROW(predicate(symbols{{}}), invalid_variable_exception);
    
    rule r;
    r.maps_to(predicate);
    EXPECT_EQ(r.apply({{}}), 0); // Apply should return the fallback value after catching exception
    
}

TEST(rule, test_rule_predicate_condition) {
    
    rule r;
    r.maps_to([](const symbols&) {
        return 1;
    });
    r.cell_satisfies_predicate({0, 0}, [](const int val) { return val > 5; });

    ASSERT_EQ(r.conditions.size(), 1);  // Assert vector is populated
    ASSERT_TRUE(r.conditions[0].predicate(6));  // Assert positive case
    ASSERT_EQ(r.apply({{6}}), 1);  // Assert positive case for apply
    ASSERT_EQ(r.apply({{4}}), 0);  // Assert negative case for apply
    
}

TEST(rule, test_rule_scalar_condition) {
    
    rule r;
    r.maps_to([](const symbols&) {
        return 1;
    });
    r.cell_matches_scalar({0, 0}, 5);

    ASSERT_EQ(r.conditions.size(), 1);  // Assert vector is populated
    ASSERT_TRUE(r.conditions[0].predicate(5));  // Assert predicate checks correctly
    ASSERT_EQ(r.apply({{5}}), 1);  // Assert positive case for apply
    ASSERT_EQ(r.apply({{4}}), 0);  // Assert negative case for apply
    
}

TEST(rule, test_rule_negative_relative_coords) {
    
    rule r;
    r.maps_to([](const symbols&) {
        return 1;
    });
    r.cell_matches_scalar({-1, 0}, 5);
    r.cell_matches_scalar({0, -1}, 4);

    EXPECT_EQ(r.conditions.size(), 2);  // Assert vector is populated
    EXPECT_TRUE(r.conditions[0].predicate(5));  // Assert predicate checks correctly
    EXPECT_TRUE(r.conditions[1].predicate(4));  // Assert predicate checks correctly
    EXPECT_EQ(r.apply({
        {0, 4, 0},
        {5, 0, 0},
        {0, 0, 0}
    }), 1);  // Assert positive case for apply
    
}

TEST(rule, test_rule_radius) {
    rule r;

    // Initially, the radius should be zero
    EXPECT_EQ(r.radius(), 0);

    // Add a predicate at (1, 1), which should update the radius to 1
    r.cell_satisfies_predicate({1, 1}, [](const int) { return false; });
    EXPECT_EQ(r.radius(), 1);

    // Add a variable at (-2, 0), which should update the radius to 2
    r.variable_cell({-2, 0}, 'a');
    EXPECT_EQ(r.radius(), 2);

    // Add another variable at (1, 1), which should not update the radius
    // because it's already within the bounds of the current radius
    r.variable_cell({1, 1}, 'b');
    EXPECT_EQ(r.radius(), 2);
}

class MaskingRuleAutomatonTest : public AutomatonTestFixtures {
    // No need for additional setup and teardown here
};

INSTANTIATE_TEST_CASE_P(
    BackendTypes,
    MaskingRuleAutomatonTest,
    ::testing::ValuesIn(MaskingRuleAutomatonTest::shared_params()),
    custom_test_name<MaskingRuleAutomatonTest>
);

TEST_P(MaskingRuleAutomatonTest, test_masking_rule_automaton_with_scalar)
{
    
    const auto backend = get_backend({2, 3});
    
    // create a simple rule
    const auto r = rule()
        .cell_matches_scalar({0, -1}, 3)
        .variable_cell({0, -1}, 'a')
        .maps_to([](const symbols& vars){return vars.value_of('a') - 1;});

    masking_rule_automaton automaton(backend.get(), r);

    // Set initial state to look like this
    // 0 0
    // 0 0
    // 3 0

    automaton.set_value(0, 0, 3);

    auto diffs = automaton.tick();

    // Expect the automaton to look like this
    // 0 0
    // 2 0
    // 0 0
    
    EXPECT_EQ(diffs.size(), 2);
    EXPECT_EQ(diffs[0].x, 0);
    EXPECT_EQ(diffs[0].y, 0);
    EXPECT_EQ(diffs[0].old_value, 3);
    EXPECT_EQ(diffs[0].new_value, 0);
    EXPECT_EQ(diffs[1].x, 0);
    EXPECT_EQ(diffs[1].y, 1);
    EXPECT_EQ(diffs[1].old_value, 0);
    EXPECT_EQ(diffs[1].new_value, 2);

    diffs = automaton.tick();

    // Middle cell should be killed since 2 doesn't match scalar
    
    EXPECT_EQ(diffs.size(), 1);
    EXPECT_EQ(diffs[0].x, 0);
    EXPECT_EQ(diffs[0].y, 1);
    EXPECT_EQ(diffs[0].old_value, 2);
    EXPECT_EQ(diffs[0].new_value, 0);

    diffs = automaton.tick();

    EXPECT_EQ(diffs.size(), 0);
    
}