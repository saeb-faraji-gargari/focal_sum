#include "dc/focal_sum.hpp"
#include "dc/neighborhood_node.hpp"
#include "dc/raster.hpp"
#include "mdspan.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
namespace {
    float sum_(float& argument_1, float& argument_2)
    {
        return argument_1 + argument_2;
    }
}  // namespace
namespace dc {
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
    Raster focal_sum(Raster const& input, int const window_size)
    {
        int const ncols = input.get_size_x();
        int const nrows = input.get_size_y();
        float const no_data_value = input.noData_value;
        Raster output(ncols, nrows);
        float max_range_value{std::numeric_limits<float>::max()};
        std::mdspan input_2D{input.value.data(), nrows, ncols};
        std::mdspan output_2D{output.value.data(), nrows, ncols};
        for (int I_row = 0; I_row < nrows; I_row++)
        {
            for (int I_col = 0; I_col < ncols; I_col++)
            {
                float sum_local{0.0};
                // float value_center_node = input_2D(j, i);
                float const& value_center_node = input_2D(I_row, I_col);
                if (check_no_data(const_cast<float&>(value_center_node), no_data_value))
                {
                    output_2D(I_row, I_col) = no_data_value;
                }
                else
                {
                    for (int row_window = -window_size; row_window <= window_size; row_window++)
                    {
                        for (int col_womdow = -window_size; col_womdow <= window_size; col_womdow++)
                        {
                            if ((row_window + I_row >= 0) && (col_womdow + I_col >= 0) &&
                                (row_window + I_row < nrows) && (col_womdow + I_col < ncols))
                            {
                                float value_neighborhood_node =
                                    input_2D(row_window + I_row, col_womdow + I_col);
                                if (std::isnan(value_neighborhood_node))
                                {
                                    output_2D(I_row, I_col) = no_data_value;
                                }
                                else
                                {
                                    if (!(check_no_data(value_neighborhood_node, no_data_value)))
                                    {
                                        sum_local = sum_(sum_local, value_neighborhood_node);
                                    }
                                    if (check_out_of_range(sum_local, max_range_value))
                                    {
                                        output_2D(I_row, I_col) = no_data_value;
                                    }
                                }
                                /*
                                std::cout << "i:" << i << " j:" << j << " ii:" << ii << " jj:" << jj
                                          << " sum_local:" << sum_local << " output_2D(j,i):" << output_2D(j,
                                i);

                                double chert_pert;
                                std::cin >> chert_pert;
                                */
                            }
                        }
                        output_2D(I_row, I_col) = sum_local;
                    }
                }
            }
        }
        return output;
    }
}  // namespace dc