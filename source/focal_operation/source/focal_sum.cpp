#include "dc/focal_sum.hpp"
#include "dc/neighborhood_node.hpp"
#include "dc/raster.hpp"
#include <limits>

namespace dc {

    float sum_neighborhood(
        Raster const& input, std::vector<int> const& neighborhood_node_ID, float const& no_data_value);

    float sum_(float& argument_1, float& argument_2);

    bool check_no_data(float& argument, float const& no_data_value);

    bool check_out_of_range(float& argument, float& max_range_value);

    const Raster focal_sum(Raster const& input, int const window_size_x, int const window_size_y)
    {

        int const ncols = input.size_x;
        int const nrows = input.size_y;

        float const no_data_value = input.noData_value;

        Raster output(ncols, nrows);

        for (int i = 0; i < (ncols * nrows); i++)
        {

            std::vector<int> neighborhood_node_ID =
                neighborhood_node(ncols, nrows, window_size_x, window_size_y, i);

            output.value[i] = sum_neighborhood(input, neighborhood_node_ID, no_data_value);
        }

        return output;
    }

    float sum_neighborhood(
        Raster const& input, std::vector<int> const& neighborhood_node_ID, float const& no_data_value)
    {
        float max_range_value {std::numeric_limits<float>::max()};
        float sum {0.0};

        for (std::size_t i = 0; i < neighborhood_node_ID.size(); i++)

        {
            float value_neighborhood_node = input.value[neighborhood_node_ID[i]];

            if ((check_no_data(value_neighborhood_node, no_data_value)) || (std::isnan(value_neighborhood_node)))
            {
                return no_data_value;
            }

            else
            {

                sum = sum_(sum, value_neighborhood_node);

                if (check_out_of_range(sum,max_range_value))
                {
                    return no_data_value;
                }
            }
        }

        return sum;
    }

    float sum_(float& argument_1, float& argument_2)

    {
        return argument_1 + argument_2;
    }

    bool check_no_data(float& argument, float const& no_data_value)

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

    bool check_out_of_range(float& argument, float& max_range_value)

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