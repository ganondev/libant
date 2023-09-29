#include "fixtures.h"
#include "../libant.h"

class SpatialStructureTest : public AutomatonTestFixtures {
    // No need for additional setup and teardown here
};

INSTANTIATE_TEST_CASE_P(
    BackendTypes,
    SpatialStructureTest,
    ::testing::ValuesIn(SpatialStructureTest::shared_params()),
    custom_test_name<SpatialStructureTest>
);

TEST_P(SpatialStructureTest, test_get_cells_around)
{
    const auto backend = get_backend({5, 5});

    // set backend to look like this:
    // 4  0 0 0 0 0
    // 3  0 1 1 1 0
    // 2  0 2 0 2 0
    // 1  0 3 3 3 0
    // 0  0 0 0 0 0
    // Y
    //  X 0 1 2 3 4

    // set backend to look like this:
    backend->insert(1, 1, 3);
    backend->insert(2, 1, 3);
    backend->insert(3, 1, 3);
    backend->insert(1, 2, 2);
    backend->insert(3, 2, 2);
    backend->insert(1, 3, 1);
    backend->insert(2, 3, 1);
    backend->insert(3, 3, 1);

    const auto cells_around = backend->get_cells_around({2, 2}, 1);

    // expect:
    // 1 1 1
    // 2 0 2
    // 3 3 3

    EXPECT_EQ(cells_around.size(), 3);
    
    // [Y][X] -- lower here corresponds to lower in the grid
    for (auto i = 0; i < cells_around.size(); i++) {
        for (auto j = 0; j < cells_around[i].size(); j++) {
            EXPECT_EQ(cells_around[i][j], backend->get_value(j + 1, i + 1));
        }
        EXPECT_EQ(cells_around[i].size(), 3);
    }
    
}

TEST_P(SpatialStructureTest, test_get_num_neighbours)
{

    const auto backend = get_backend({5, 5});

    // set backend to look like this:
    // 4  0 0 0 0 0
    // 3  0 1 1 1 0
    // 2  0 2 0 2 0
    // 1  0 3 3 3 0
    // 0  0 0 0 0 0
    // Y
    //  X 0 1 2 3 4

    // set backend to look like this:
    backend->insert(1, 1, 3);
    backend->insert(2, 1, 3);
    backend->insert(3, 1, 3);
    backend->insert(1, 2, 2);
    backend->insert(3, 2, 2);
    backend->insert(1, 3, 1);
    backend->insert(2, 3, 1);
    backend->insert(3, 3, 1);

    const auto num_neighbours = backend->count_neighbours(2, 2);

    EXPECT_EQ(num_neighbours, 8);
    
}