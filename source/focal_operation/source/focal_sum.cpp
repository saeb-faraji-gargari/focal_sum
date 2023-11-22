#include "dc/focal_sum.hpp"
#include "dc/neighborhood_node.hpp"
#include "dc/raster.hpp"
#include <algorithm>
#include <limits>

#include <iostream>

#include "mdspan.hpp"

namespace

{

    float sum_(float& argument_1, float& argument_2)

    {
        return argument_1 + argument_2;
    }
}  // namespace


namespace dc {

    bool check_no_data(float& argument, float const& no_data_value);

    bool check_out_of_range(float& argument, float const& max_range_value);

    const Raster focal_sum(Raster const& input, int const window_size_x, int const window_size_y)
    {

        int const ncols = input.size_x;
        int const nrows = input.size_y;

        float const no_data_value = input.noData_value;

        Raster output(ncols, nrows);

        /*
        std::vector<int> neighborhood_ID(window_size_x * window_size_y, 0);
        std::vector<int> node_ID_x(window_size_x, 0);
        std::vector<int> node_ID_y(window_size_y, 0);

        std::vector<int> neighborhood_ID_internal_source(window_size_x * window_size_y, 0);
        std::vector<int> neighborhood_ID_internal(window_size_x * window_size_y, 0);
        neighborhood_internal(ncols, window_size_x, window_size_y, neighborhood_ID_internal_source);
        */

        int window_size_half_x = static_cast<int>(std::round((window_size_x) / 2));
        int window_size_half_y = static_cast<int>(std::round((window_size_y) / 2));

        /*
        std::vector<int> internal_node_ID(
            (ncols - (2 * window_size_half_x)) * (nrows - (2 * window_size_half_y)), 0);

        std::vector<int> external_node_ID((ncols * nrows) - internal_node_ID.size(), 0);

        internal_ID(ncols, nrows, window_size_x, window_size_y, internal_node_ID);

        internal_external_ID(ncols, nrows, window_size_x, window_size_y, internal_node_ID, external_node_ID);
        */

        float max_range_value{std::numeric_limits<float>::max()};

        std::mdspan inpout_2D{input.value.data(), nrows, ncols};

        std::mdspan output_2D{output.value.data(), nrows, ncols};

        for (int j = 0; j < nrows; j++)
        {
            for (int i = 0; i < ncols; i++)
            {

                float sum_local{0.0};

                for (int jj = -window_size_half_y; jj <= window_size_half_y; jj++)
                {

                    for (int ii = -window_size_half_x; ii <= window_size_half_y; ii++)
                    {

                        if ((jj + j >= 0) && (ii + i >= 0) && (jj + j < nrows) && (ii + i < ncols))

                        {

                            float value_neighborhood_node = inpout_2D(jj + j, ii + i);

                            if ((check_no_data(value_neighborhood_node, no_data_value)) ||
                                (std::isnan(value_neighborhood_node)))
                            {
                                output_2D(j,i) = no_data_value;
                            }

                            else
                            {
                                sum_local = sum_(sum_local, value_neighborhood_node);

                                if (check_out_of_range(sum_local, max_range_value))
                                {
                                    output_2D(j,i) = no_data_value;
                                }
                            }
                            
                            /*
                            std::cout << "i:" << i << " j:" << j << " ii:" << ii << " jj:" << jj
                                      << " sum_local:" << sum_local << " output_2D(j,i):" << output_2D(j, i);

                            double chert_pert;
                            std::cin >> chert_pert;
                            */
                            

                        }
                    }

                    output_2D(j,i) = sum_local;
                }
                
            }
        }

        return output;
    }

    inline bool check_no_data(float& argument, float const& no_data_value)
    {
        if (argument == no_data_value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    inline bool check_out_of_range(float& argument, float const& max_range_value)

    {
        if (argument >= max_range_value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}  // namespace dc