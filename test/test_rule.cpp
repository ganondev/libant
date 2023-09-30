#include <gtest/gtest.h>

#include "../libant.h"

using namespace libant;

TEST(rule, test_rule_mapper) {
    
    rule r;

    ASSERT_EQ(r.mapper, nullptr); // Mapper should be zeroed
    
    r.maps_to([](const symbols& vars) {
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
    r.maps_to([](const symbols& vars) {
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
    r.maps_to([](const symbols& vars) {
        return 1;
    });
    r.cell_matches_scalar({0, 0}, 5);

    ASSERT_EQ(r.conditions.size(), 1);  // Assert vector is populated
    ASSERT_TRUE(r.conditions[0].predicate(5));  // Assert predicate checks correctly
    ASSERT_EQ(r.apply({{5}}), 1);  // Assert positive case for apply
    ASSERT_EQ(r.apply({{4}}), 0);  // Assert negative case for apply
    
}