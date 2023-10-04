#include "dc/focal_min.hpp"
#include "dc/neighborhood_node.hpp"

#include <algorithm>

namespace dc {

    float min_value(Raster const& input, std::vector<int> neighborhood_node_ID);

    const Raster focal_min(Raster const& input, int const& window_size_x, int const& window_size_y)

    {
        int const ncols = input.size_x;
        int const nrows = input.size_y;
        double no_data = input.noData_value;

        Raster output(ncols, nrows);

        for (std::size_t i = 0; i < (ncols * nrows); i++)
        {

            std::vector<int> neighborhood_node_ID =
                neighborhood_node(ncols, nrows, window_size_x, window_size_y, static_cast<int>(i));

            float min_cell{min_value(input, neighborhood_node_ID)};

            output.value [static_cast<int>(i)] = min_cell;
        }


        return output;
    }

    float min_value(Raster const& input, std::vector<int> neighborhood_node_ID)
    {

        std::vector<float> value_neighborhood;

        for (int i = 0; i < neighborhood_node_ID.size(); i++)

        {

            value_neighborhood.push_back(input.value[neighborhood_node_ID[i]]);
        }

        auto min_neighborhood{std::min_element(value_neighborhood.begin(), value_neighborhood.end())};

        return *min_neighborhood;
    }

}  // namespace dc