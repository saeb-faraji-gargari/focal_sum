#include "dc/focal_sum.hpp"
#include "dc/neighborhood_node.hpp"
#include "dc/raster.hpp"

namespace dc {

    double sum_neighborhood(Raster const&, std::vector<int> const&);

    const Raster focal_sum(Raster const& input, int const window_size_x, int const window_size_y)
    {
        int const ncols = input.size_x;
        int const nrows = input.size_y;
        Raster output(ncols, nrows);

        for (int i = 0; i < (ncols * nrows); i++)
        {

            std::vector<int> neighborhood_node_ID =
                neighborhood_node(ncols, nrows, window_size_x, window_size_y, i);

            output.value[i] = sum_neighborhood(input, neighborhood_node_ID);
        }

        return output;
    }

    double sum_neighborhood(Raster const& input, std::vector<int> const& neighborhood_node_ID)
    {

        double sum = 0.0;

        double noData = input.noData_value;

        for (std::size_t i = 0; i < neighborhood_node_ID.size(); i++)

        {

            if (input.value[neighborhood_node_ID[i]] == noData)
            {
                sum = noData;
            }

            else
            {

                sum = sum + input.value[neighborhood_node_ID[i]];
            }
        }

        return sum;
    }

}  // namespace dc