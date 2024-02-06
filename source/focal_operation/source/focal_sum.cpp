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

    inline bool check_no_data(float& argument, float const& no_data_value)
    {
        return argument == no_data_value;
    }

    inline bool check_out_of_range(float& argument, float const& max_range_value)

    {
        return argument >= max_range_value;
    }

    Raster focal_sum(Raster const& input, int const window_size)
    {

        int const ncols = input.get_size_x();
        int const nrows = input.get_size_y();

        float const no_data_value = input.noData_value;

        Raster output(ncols, nrows);

        // int window_size_half_x = static_cast<int>(std::round((window_size_x) / 2));
        // int window_size_half_y = static_cast<int>(std::round((window_size_y) / 2));

        float max_range_value{std::numeric_limits<float>::max()};

        // std::mdspan input_2D{input.value.data(), nrows, ncols};
        // std::mdspan output_2D{output.value.data(), nrows, ncols};

        Kokkos::mdspan input_2D{input.value.data(), nrows, ncols};
        Kokkos::mdspan output_2D{output.value.data(), nrows, ncols};

        for (int row = 0; row < nrows; row++)
        {
            for (int col = 0; col < ncols; col++)
            {

                float sum_local{0.0};

                float const& value_center_cell = input_2D(row, col);

                if (check_no_data(const_cast<float&>(value_center_cell), no_data_value))
                {
                    output_2D(row, col) = no_data_value;
                }
                else
                {
                    for (int row_window = -window_size; row_window <= window_size; row_window++)
                    {
                        for (int col_window = -window_size; col_window <= window_size; col_window++)
                        {

                            if ((row_window + row >= 0) && (col_window + col >= 0) &&
                                (row_window + row < nrows) && (col_window + col < ncols))

                            {
                                float value_neighborhood_cell = input_2D(row_window + row, col_window + col);

                                if (std::isnan(value_neighborhood_cell))
                                {
                                    output_2D(row, col) = no_data_value;
                                }
                                else
                                {
                                    if (!(check_no_data(value_neighborhood_cell, no_data_value)))
                                    {
                                        {
                                            sum_local = sum_(sum_local, value_neighborhood_cell);

                                            if (check_out_of_range(sum_local, max_range_value))
                                            {
                                                output_2D(row, col) = no_data_value;
                                            }
                                            else
                                            {
                                                output_2D(row, col) = sum_local;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return output;
    }

}  // namespace dc
