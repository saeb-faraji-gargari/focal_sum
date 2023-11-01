#include "dc/focal_sum.hpp"
#include "dc/neighborhood_node.hpp"
#include "dc/raster.hpp"
#include <algorithm>
#include <limits>

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

    float sum_(float& argument_1, float& argument_2);

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

        std::vector<int> internal_ID_vectro(
            (ncols - (2 * window_size_half_x)) * (nrows - (2 * window_size_half_y)), 0);

        std::vector<int> external_ID_vectro(
            (ncols * nrows) - ((2 * window_size_half_x) * (nrows - (2 * window_size_half_y))), 0);

        internal_ID(ncols, nrows, window_size_x, window_size_y, internal_ID_vectro);

        internal_external_ID(
            ncols, nrows, window_size_x, window_size_y, internal_ID_vectro, external_ID_vectro);


        float max_range_value{std::numeric_limits<float>::max()};

        /* for (int ID = 0; ID < (ncols * nrows); ID++)
        {

            if (std::find(internal_ID_vectro.begin(), internal_ID_vectro.end(), ID)
        !=internal_ID_vectro.end())
            {
                output.value[ID] = sum_neighborhood_internal(
                    input, ID, neighborhood_ID_internal_source, no_data_value, max_range_value);
            }
            else
            {
                neighborhood_node(
                    ncols, nrows, window_size_x, window_size_y, ID, node_ID_x, node_ID_y, neighborhood_ID);

                output.value[ID] = sum_neighborhood(input, neighborhood_ID, no_data_value, max_range_value);
            }
        } */

        for (int i = 0; i < internal_ID_vectro.size(); i++)
        {
            output.value[internal_ID_vectro[i]] = sum_neighborhood_internal(
                input,
                internal_ID_vectro[i],
                neighborhood_ID_internal_source,
                no_data_value,
                max_range_value);
        }

        for (int i = 0; i < external_ID_vectro.size(); i++)
        {
            neighborhood_node(
                ncols,
                nrows,
                window_size_x,
                window_size_y,
                external_ID_vectro[i],
                node_ID_x,
                node_ID_y,
                neighborhood_ID);

            output.value[external_ID_vectro[i]] =
                sum_neighborhood(input, neighborhood_ID, no_data_value, max_range_value);
        }


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


    float sum_neighborhood(
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

    bool check_out_of_range(float& argument, float const& max_range_value)

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