#define BOOST_TEST_MODULE TestModuleNeighborhood

#include <boost/test/unit_test.hpp>

#include "dc/neighborhood_node.hpp"
#include <iostream>


BOOST_AUTO_TEST_CASE(test_neighborhood_internal_midle_point)
{
    //----------This test midle point neighborhood nodes for 3*3 window------------------------

    BOOST_TEST_MESSAGE("Running test_midle_point");

    int ncols = 6;
    int nrows = 6;
    int window_size_x = 3;
    int window_size_y = 3;
    int node_ID = 55;

    std::vector<int> result_neighborhood_ID(window_size_x * window_size_y, 0);
    // std::vector<int> node_ID_x(window_size_x, 0);
    // std::vector<int> node_ID_y(window_size_y, 0);

    dc::neighborhood_internal(ncols, window_size_x, window_size_y, result_neighborhood_ID);

    /*std::cout << "Result neighborhood_ID: ";
    double chert_pert;
    std::cin >> chert_pert;

    // Print the contents
    std::cout << "Result neighborhood_ID: ";
    for (int val : result_neighborhood_ID) {
        std::cout << val << " ";
    }

    std::cout << std::endl;*/

    std::vector<int> output_exact = {-7, -6, -5, -1, 0, 1, 5, 6, 7};

    BOOST_CHECK_EQUAL_COLLECTIONS(
        result_neighborhood_ID.begin(),
        result_neighborhood_ID.end(),
        output_exact.begin(),
        output_exact.end());
}

BOOST_AUTO_TEST_CASE(test_midle_point)
{
    //----------This test midle point neighborhood nodes for 3*3 window------------------------

    BOOST_TEST_MESSAGE("Running test_midle_point");

    int ncols = 10;
    int nrows = 10;
    int window_size_x = 3;
    int window_size_y = 3;
    int node_ID = 55;

    std::vector<int> result_neighborhood_ID(window_size_x * window_size_y, 0);
    std::vector<int> node_ID_x(window_size_x, 0);
    std::vector<int> node_ID_y(window_size_y, 0);

    dc::neighborhood_node(
        ncols, nrows, window_size_x, window_size_y, node_ID, node_ID_x, node_ID_y, result_neighborhood_ID);

    std::vector<int> output_exact = {55, 56, 54, 65, 66, 64, 45, 46, 44};

    BOOST_CHECK_EQUAL_COLLECTIONS(
        result_neighborhood_ID.begin(),
        result_neighborhood_ID.end(),
        output_exact.begin(),
        output_exact.end());
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

    std::vector<int> result_neighborhood_ID(window_size_x * window_size_y, 0);
    std::vector<int> node_ID_x(window_size_x, 0);
    std::vector<int> node_ID_y(window_size_y, 0);

    dc::neighborhood_node(
        ncols, nrows, window_size_x, window_size_y, node_ID, node_ID_x, node_ID_y, result_neighborhood_ID);

    std::vector<int> output_exact = {0, 1, 2, 10, 11, 12, 20, 21, 22};

    BOOST_CHECK_EQUAL_COLLECTIONS(
        result_neighborhood_ID.begin(),
        result_neighborhood_ID.end(),
        output_exact.begin(),
        output_exact.end());
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

    std::vector<int> result_neighborhood_ID(window_size_x * window_size_y, 0);
    std::vector<int> node_ID_x(window_size_x, 0);
    std::vector<int> node_ID_y(window_size_y, 0);

    dc::neighborhood_node(
        ncols, nrows, window_size_x, window_size_y, node_ID, node_ID_x, node_ID_y, result_neighborhood_ID);

    std::vector<int> output_exact = {79, 77, 78, 59, 57, 58, 69, 67, 68};

    BOOST_CHECK_EQUAL_COLLECTIONS(
        result_neighborhood_ID.begin(),
        result_neighborhood_ID.end(),
        output_exact.begin(),
        output_exact.end());
}
