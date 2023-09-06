#define BOOST_TEST_MODULE TestModuleNeighborhood
#include <boost/test/unit_test.hpp>

#include "dc/neighborhood_node.hpp"
#include <iostream>

BOOST_AUTO_TEST_CASE(test_midle_point)
{
    //----------This test midle point neighborhood nodes for 3*3 window------------------------

    BOOST_TEST_MESSAGE("Running test_midle_point");

    int ncols = 10;
    int nrows = 10;
    int window_size_x = 3;
    int window_size_y = 3;
    int node_ID = 55;

    std::vector<int> result_neighborhood_ID =
        dc::neighborhood_node(ncols, nrows, window_size_x, window_size_y, node_ID);

    std::cout << "result_neighborhood_ID test_1 midle point 3*3 window:" << std::endl;
    for (size_t i = 0; i < result_neighborhood_ID.size(); ++i)
    {
        std::cout << result_neighborhood_ID[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> output_exact_midle_point = {55, 56, 54, 65, 66, 64, 45, 46, 44};

    BOOST_TEST(result_neighborhood_ID == output_exact_midle_point);
}

BOOST_AUTO_TEST_CASE(test_up_left_point)
{
    //----------This test left-up point neighborhood nodes for 3*3 window---------------

    BOOST_TEST_MESSAGE("Running test_up_left_point");

    int ncols = 10;
    int nrows = 10;
    int window_size_x = 3;
    int window_size_y = 3;
    int node_ID = 0;

    bool status = false;

    std::vector<int> result_neighborhood_ID =
        dc::neighborhood_node(ncols, nrows, window_size_x, window_size_y, node_ID);

    std::cout << "result_neighborhood_ID left-up point 3*3 window:" << std::endl;
    for (size_t i = 0; i < result_neighborhood_ID.size(); ++i)
    {
        std::cout << result_neighborhood_ID[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> output_exact_midle_point = {0, 1, 2, 10, 11, 12, 20, 21, 22};

    BOOST_TEST(result_neighborhood_ID == output_exact_midle_point);
}

BOOST_AUTO_TEST_CASE(test_right_bottom_point)
{
    //----------This test right_bottom point neighborhood nodes for 3*3 window------------------------

    BOOST_TEST_MESSAGE("Running test_right_bottom_point");

    int ncols = 10;
    int nrows = 8;
    int window_size_x = 3;
    int window_size_y = 3;
    int node_ID = 79;

    bool status = false;

    std::vector<int> result_neighborhood_ID =
        dc::neighborhood_node(ncols, nrows, window_size_x, window_size_y, node_ID);

    std::cout << "result_neighborhood_ID test_1 midle point 3*3 window:" << std::endl;
    for (size_t i = 0; i < result_neighborhood_ID.size(); ++i)
    {
        std::cout << result_neighborhood_ID[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> output_exact_midle_point = {79, 77, 78, 59, 57, 58, 69, 67, 68};

    // BOOST_TEST(result_neighborhood_ID == output_exact_midle_point);
    BOOST_TEST_REQUIRE(result_neighborhood_ID == output_exact_midle_point);
}
