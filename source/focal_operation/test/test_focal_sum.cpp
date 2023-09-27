#define BOOST_TEST_MODULE Test_focal_sum

#include <boost/test/unit_test.hpp>

#include "dc/focal_sum.hpp"
#include "dc/raster.hpp"
#include <vector>

#include <limits>

BOOST_AUTO_TEST_CASE(test_3_to_3_windows)
{
    //----------This test focal sum for 3*3 window------------------------

    const int ncols = 3;
    const int nrows = 4;

    dc::Raster input_raster(ncols, nrows);

    std::vector<float> input_vector = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.1, 11.11, 12.12};

    input_raster.value = input_vector;

    std::vector<float> output_exact_vector = {49.50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const dc::Raster output_vector = dc::focal_sum(input_raster, 3, 3);

    BOOST_CHECK_EQUAL(output_vector.value[0], output_exact_vector[0]);
}


BOOST_AUTO_TEST_CASE(test_no_data)
{
    //----------This test focal sum for 3*3 window------------------------

    const int ncols = 3;
    const int nrows = 4;

    dc::Raster input_raster(ncols, nrows);

    // std::vector<float> input_vector = {-1e+10, -2.2e+10, -3.3e+10, -4.4e+10, -5.5e+10, -6.6e+10, -7.7e+10,
    // -8.8e+10, -9.9e+10, -10.1e+10, -11.11e+10, -12.12e+10};
    std::vector<float> input_vector = {-1e+10, -88000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    input_raster.value = input_vector;

    input_raster.noData_value = -1e+10;

    std::vector<float> output_exact_vector = {
        -1e+10, -1e+10, -1e+10, 0, -1e+10, -1e+10, -1e+10, 0, -1e+10, -1e+10, -1e+10, 0};

    const dc::Raster output_vector = dc::focal_sum(input_raster, 3, 3);

    BOOST_CHECK_EQUAL(output_vector.value[0], output_exact_vector[0]);
}


BOOST_AUTO_TEST_CASE(test_max_value)
{
    //----------This test focal sum for 3*3 window------------------------

    const int ncols = 3;
    const int nrows = 4;

    dc::Raster input_raster(ncols, nrows);

    float max_value_ot_of_range = std::numeric_limits<float>::max();

    input_raster.noData_value = -1e+10;

    std::vector<float> input_vector = {
        max_value_ot_of_range / 2,
        max_value_ot_of_range / 2,
        max_value_ot_of_range / 2,
        max_value_ot_of_range / 2,
        max_value_ot_of_range / 2,
        max_value_ot_of_range / 2,
        max_value_ot_of_range / 2,
        0,
        -890,
        0,
        88,
        789};

    input_raster.value = input_vector;

    std::vector<float> output_exact_vector = {-1e+10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const dc::Raster output_vector = dc::focal_sum(input_raster, 3, 3);

    BOOST_CHECK_EQUAL(output_vector.value[0], output_exact_vector[0]);
}
