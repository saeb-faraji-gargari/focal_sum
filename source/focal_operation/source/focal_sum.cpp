#include "dc/focal_sum.hpp"
#include "dc/neighborhood_node.hpp"
#include "dc/raster.hpp"
#include <limits>

namespace dc {

    double sum_neighborhood(
        Raster const& input, std::vector<int> const& neighborhood_node_ID, float const& no_data);

    const Raster focal_sum(Raster const& input, int const window_size_x, int const window_size_y)
    {

        int const ncols = input.size_x;
        int const nrows = input.size_y;

        float const no_data = input.noData_value;

        Raster output(ncols, nrows);

        for (int i = 0; i < (ncols * nrows); i++)
        {

            std::vector<int> neighborhood_node_ID =
                neighborhood_node(ncols, nrows, window_size_x, window_size_y, i);

            output.value[i] = sum_neighborhood(input, neighborhood_node_ID, no_data);
        }

        return output;
    }

    double sum_neighborhood(
        Raster const& input, std::vector<int> const& neighborhood_node_ID, float const& no_data)
    {

        double sum = 0.0;

        for (std::size_t i = 0; i < neighborhood_node_ID.size(); i++)

        {

            if ((input.value[neighborhood_node_ID[i]] == no_data) ||
                (std::isnan(input.value[neighborhood_node_ID[i]])))
            {

                return no_data;
            }

            else
            {

                sum = sum + input.value[neighborhood_node_ID[i]];

                if (sum >= std::numeric_limits<float>::max())
                {

                    return no_data;
                }
            }
        }

        return sum;
    }

}  // namespace dc