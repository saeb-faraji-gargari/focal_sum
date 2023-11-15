#include "dc/focal_sum.hpp"
#include "dc/neighborhood_node.hpp"
#include "dc/raster.hpp"
#include <algorithm>
#include <limits>

#include <iostream>

//#include <span>
#include "mdspan.hpp"

namespace

{

    float sum_(float& argument_1, float& argument_2)

    {
        return argument_1 + argument_2;
    }
}  // namespace


namespace dc {


    float sum_neighborhood(
        Raster const& input,
        std::vector<int> const& neighborhood_node_ID,
        float const& no_data_value,
        float const& max_range_value);

    float sum_neighborhood_internal(
        Raster const& input,
        int const node_ID,
        std::vector<int> const& neighborhood_ID_internal_source,
        float const& no_data_value,
        float const& max_range_value);

    bool check_no_data(float& argument, float const& no_data_value);

    bool check_out_of_range(float& argument, float const& max_range_value);

    const Raster focal_sum(Raster const& input, int const window_size_x, int const window_size_y)
    {

        int const ncols = input.size_x;
        int const nrows = input.size_y;

        float const no_data_value = input.noData_value;

        Raster output(ncols, nrows);

        std::vector<int> neighborhood_ID(window_size_x * window_size_y, 0);
        std::vector<int> node_ID_x(window_size_x, 0);
        std::vector<int> node_ID_y(window_size_y, 0);

        std::vector<int> neighborhood_ID_internal_source(window_size_x * window_size_y, 0);
        std::vector<int> neighborhood_ID_internal(window_size_x * window_size_y, 0);
        neighborhood_internal(ncols, window_size_x, window_size_y, neighborhood_ID_internal_source);

        int window_size_half_x = static_cast<int>(std::round((window_size_x) / 2));
        int window_size_half_y = static_cast<int>(std::round((window_size_y) / 2));

        std::vector<int> internal_node_ID(
            (ncols - (2 * window_size_half_x)) * (nrows - (2 * window_size_half_y)), 0);

        std::vector<int> external_node_ID((ncols * nrows) - internal_node_ID.size(), 0);

        internal_ID(ncols, nrows, window_size_x, window_size_y, internal_node_ID);

        internal_external_ID(
            ncols, nrows, window_size_x, window_size_y, internal_node_ID, external_node_ID);


        float max_range_value{std::numeric_limits<float>::max()};


        for (int i = 0; i < internal_node_ID.size(); i++)
        {
            output.value[internal_node_ID[i]] = sum_neighborhood_internal(
                input,
                internal_node_ID[i],
                neighborhood_ID_internal_source,
                no_data_value,
                max_range_value);
        }

        for (int i = 0; i < external_node_ID.size(); i++)
        {
            neighborhood_node(
                ncols,
                nrows,
                window_size_x,
                window_size_y,
                external_node_ID[i],
                node_ID_x,
                node_ID_y,
                neighborhood_ID);

            output.value[external_node_ID[i]] =
                sum_neighborhood(input, neighborhood_ID, no_data_value, max_range_value);
        }

        std::cout << "ncols: " << ncols << std::endl;
        std::cout << "nrows: " << nrows << std::endl;
        std::cout << "internal_ID_vectro.size: " << internal_node_ID.size() << std::endl;
        std::cout << "external_ID_vectro.size: " << external_node_ID.size() << std::endl;
        
        std::mdspan output_2D{output.value.data(), nrows, ncols};

        //std::cout << "output_2D(3,5): " << output_2D(3,5) << std::endl;

        
        return output;
    }

    float sum_neighborhood_internal(
        Raster const& input,
        int const node_ID,
        std::vector<int> const& neighborhood_ID_internal_source,
        float const& no_data_value,
        float const& max_range_value)
    {
        float sum{0.0};

        //for (const auto& i : neighborhood_ID_internal_source)

        for (std::size_t i = 0; i < neighborhood_ID_internal_source.size(); i++)

        {
            float value_neighborhood_node = input.value[neighborhood_ID_internal_source[i] + node_ID];

            if ((check_no_data(value_neighborhood_node, no_data_value)) ||
                (std::isnan(value_neighborhood_node)))
            {
                return no_data_value;
            }

            else
            {
                sum = sum_(sum, value_neighborhood_node);

                if (check_out_of_range(sum, max_range_value))
                {
                    return no_data_value;
                }
            }
        }

        return sum;
    }


    inline float sum_neighborhood(
        Raster const& input,
        std::vector<int> const& neighborhood_ID,
        float const& no_data_value,
        float const& max_range_value)
    {
        float sum{0.0};

        for (std::size_t i = 0; i < neighborhood_ID.size(); i++)

        {
            float value_neighborhood_node = input.value[neighborhood_ID[i]];

            if ((check_no_data(value_neighborhood_node, no_data_value)) ||
                (std::isnan(value_neighborhood_node)))
            {
                return no_data_value;
            }

            else
            {

                sum = sum_(sum, value_neighborhood_node);

                if (check_out_of_range(sum, max_range_value))
                {
                    return no_data_value;
                }
            }
        }

        return sum;
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