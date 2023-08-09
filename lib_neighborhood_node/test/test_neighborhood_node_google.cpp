
#include "dc/neighborhood_node.hpp"
#include <gtest/gtest.h>

TEST(NeighborhoodNodeTest, ExampleTest)
{
    int ncols = 10;
    int nrows = 10;
    int window_size_x = 3;
    int window_size_y = 3;
    int node_ID = 55;

    std::vector<int> expected_neighborhood_ID = {56, 55, 57, 8};

    std::vector<int> result_neighborhood_ID =
        dc::neighborhood_node(ncols, nrows, window_size_x, window_size_y, node_ID);

    EXPECT_EQ(result_neighborhood_ID, expected_neighborhood_ID);
}
