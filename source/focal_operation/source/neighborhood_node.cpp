#include "dc/neighborhood_node.hpp"

#include <iostream>

namespace dc {

    void internal_ID(
        int const ncols,
        int const nrows,
        int const window_size_x,
        int const window_size_y,
        std::vector<int>& internal_ID_vectro)
    {
        int window_size_half_x = static_cast<int>(std::round((window_size_x) / 2));
        int window_size_half_y = static_cast<int>(std::round((window_size_y) / 2));

        int k = 0;
        for (int j = window_size_half_y; j < nrows - window_size_half_y; j++)
        {
            for (int i = window_size_half_x; i < ncols - window_size_half_x; i++)
            {
                internal_ID_vectro[k] = (j * ncols) + i;
                k++;
            }
        }
    }

    void internal_external_ID(
        int const ncols,
        int const nrows,
        int const window_size_x,
        int const window_size_y,
        std::vector<int>& internal_ID_vectro,
        std::vector<int>& external_ID_vectro)
    {
        int window_size_half_x = static_cast<int>(std::round((window_size_x) / 2));
        int window_size_half_y = static_cast<int>(std::round((window_size_y) / 2));

        int k_internal = 0;
        int k_external = 0;

        for (int j = 0; j < nrows; j++)
        {
            for (int i = 0; i < ncols; i++)
            {
                if ((j >= window_size_half_y) && (j < nrows - window_size_half_y) &&
                    (i >= window_size_half_x) && (i < ncols - window_size_half_x))
                {
                    internal_ID_vectro[k_internal] = (j * ncols) + i;
                    k_internal++;
                }
                else
                {
                    external_ID_vectro[k_internal] = (j * ncols) + i;
                    k_external++;
                }
            }
        }
    }

    void neighborhood_internal(
        int const ncols,
        int const window_size_x,
        int const window_size_y,
        std::vector<int>& neighborhood_ID_internal)
    {

        int iterations_x = static_cast<int>(std::round((window_size_x) / 2));
        int iterations_y = static_cast<int>(std::round((window_size_y) / 2));

        std::size_t i = 0;

        for (int i_y = -iterations_y; i_y <= iterations_y; i_y++)
        {

            for (int i_x = -iterations_x; i_x <= iterations_x; i_x++)
            {

                neighborhood_ID_internal[i] = i_x + (i_y * ncols);
                i = i + 1;
            }
        }
    }


    void neighborhood_node(
        int const ncols,
        int const nrows,
        int const window_size_x,
        int const window_size_y,
        int const node_ID,
        std::vector<int>& node_ID_x,
        std::vector<int>& node_ID_y,
        std::vector<int>& neighborhood_ID)
    {

        std::size_t iterations_x = static_cast<std::size_t>(std::round((window_size_x) / 2));
        std::size_t iterations_y = static_cast<std::size_t>(std::round((window_size_y) / 2));

        node_ID_x[0] = 0;

        for (int i = 1; i <= iterations_x; i++)
        {

            int row_num_node = static_cast<int>(std::round(node_ID / ncols));

            if ((node_ID - i) < (row_num_node * ncols))
            {
                node_ID_x[i] = i;
                node_ID_x[i + iterations_x] = iterations_x + i;
            }
            else if (node_ID + i > (((row_num_node + 1) * ncols) - 1))
            {

                node_ID_x[i] = -iterations_x - i;
                node_ID_x[i + iterations_x] = -i;
            }
            else
            {

                node_ID_x[i] = i;
                node_ID_x[i + iterations_x] = -i;
            }
        }

        node_ID_y[0] = node_ID;

        for (int i = 1; i <= iterations_y; i++)
        {

            if (node_ID + (i * ncols) > (nrows * ncols))
            {

                node_ID_y[i] = node_ID - ((i + iterations_y) * ncols);
                node_ID_y[i + iterations_y] = node_ID - (i * ncols);
            }

            else if (node_ID - (i * ncols) < 0)

            {

                node_ID_y[i] = node_ID + (i * ncols);
                node_ID_y[i + iterations_y] = node_ID + ((i + iterations_y) * ncols);
            }

            else
            {

                node_ID_y[i] = node_ID + (i * ncols);
                node_ID_y[i + iterations_y] = node_ID - (i * ncols);
            }
        }

        std::size_t i = 0;

        for (std::size_t i_y = 0; i_y < (window_size_y); i_y++)
        {

            for (std::size_t i_x = 0; i_x < (window_size_x); i_x++)
            {

                neighborhood_ID[i] = node_ID_y[i_y] + node_ID_x[i_x];
                i = i + 1;
            }
        }
    }

}  // namespace dc