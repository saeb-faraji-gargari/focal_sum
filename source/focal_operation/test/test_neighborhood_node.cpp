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


BOOST_AUTO_TEST_CASE(test_internal_ID)
{
    //----------This test midle point neighborhood nodes for 3*3 window------------------------

    BOOST_TEST_MESSAGE("Running test_midle_point");

    int ncols = 10;
    int nrows = 10;
    int window_size_x = 3;
    int window_size_y = 3;
    // int node_ID = 55;

    std::vector<int> result_neighborhood_ID(window_size_x * window_size_y, 0);
    std::vector<int> node_ID_x(window_size_x, 0);
    std::vector<int> node_ID_y(window_size_y, 0);

    int window_size_half_x = static_cast<int>(std::round((window_size_x) / 2));
    int window_size_half_y = static_cast<int>(std::round((window_size_y) / 2));

    std::vector<int> internal_ID_vectro(
        (ncols - (2 * window_size_half_x)) * (nrows - (2 * window_size_half_y)), 0);

    dc::internal_ID(ncols, nrows, window_size_x, window_size_y, internal_ID_vectro);

    std::vector<int> output_exact = {11, 12, 13, 14, 15, 16, 17, 18, 21, 22, 23, 24, 25, 26, 27, 28,
                                     31, 32, 33, 34, 35, 36, 37, 38, 41, 42, 43, 44, 45, 46, 47, 48,
                                     51, 52, 53, 54, 55, 56, 57, 58, 61, 62, 63, 64, 65, 66, 67, 68,
                                     71, 72, 73, 74, 75, 76, 77, 78, 81, 82, 83, 84, 85, 86, 87, 88};

    std::cout << "internal_ID_vectro: " << std::endl;
    for (int element : internal_ID_vectro)
    {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    BOOST_CHECK_EQUAL_COLLECTIONS(
        internal_ID_vectro.begin(), internal_ID_vectro.end(), output_exact.begin(), output_exact.end());
}

BOOST_AUTO_TEST_CASE(test_internal_external_ID)
{
    //----------This test midle point neighborhood nodes for 3*3 window------------------------

    BOOST_TEST_MESSAGE("Running test_midle_point");

    int ncols = 10;
    int nrows = 10;
    int window_size_x = 3;
    int window_size_y = 3;
    // int node_ID = 55;

    std::vector<int> result_neighborhood_ID(window_size_x * window_size_y, 0);
    std::vector<int> node_ID_x(window_size_x, 0);
    std::vector<int> node_ID_y(window_size_y, 0);

    int window_size_half_x = static_cast<int>(std::round((window_size_x) / 2));
    int window_size_half_y = static_cast<int>(std::round((window_size_y) / 2));

    std::vector<int> internal_ID_vectro(
        (ncols - (2 * window_size_half_x)) * (nrows - (2 * window_size_half_y)), 0);

    std::vector<int> external_ID_vectro(
        (ncols * nrows) - ((2 * window_size_half_x) * (nrows - (2 * window_size_half_y))), 0);

    dc::internal_external_ID(
        ncols, nrows, window_size_x, window_size_y, internal_ID_vectro, external_ID_vectro);

    std::vector<int> output_exact_internal = {11, 12, 13, 14, 15, 16, 17, 18, 21, 22, 23, 24, 25, 26, 27, 28,
                                              31, 32, 33, 34, 35, 36, 37, 38, 41, 42, 43, 44, 45, 46, 47, 48,
                                              51, 52, 53, 54, 55, 56, 57, 58, 61, 62, 63, 64, 65, 66, 67, 68,
                                              71, 72, 73, 74, 75, 76, 77, 78, 81, 82, 83, 84, 85, 86, 87, 88};

    std::vector<int> output_exact_external = {0,  1,  3,  4,  5,  6,  7,  8,  9,  10, 19, 20,
                                              29, 30, 39, 40, 49, 50, 59, 60, 69, 70, 70, 80,
                                              89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99};

    std::cout << "internal_ID_vectro: " << std::endl;
    for (int element : internal_ID_vectro)
    {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    std::cout << "output_exact_external: " << std::endl;
    for (int element : output_exact_external)
    {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    BOOST_CHECK_EQUAL_COLLECTIONS(
        internal_ID_vectro.begin(),
        internal_ID_vectro.end(),
        output_exact_internal.begin(),
        output_exact_internal.end());
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
