#define BOOST_TEST_MODULE Test_focal_sum
#include <boost/test/unit_test.hpp>

#include "dc/focal_sum.hpp"
#include "dc/raster.hpp"
#include <vector>

#include <iostream>


BOOST_AUTO_TEST_CASE(test_midle_point)
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
