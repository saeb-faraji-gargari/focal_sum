#include "dc/neighborhood_node.hpp"

#include <iostream>  //   ---------------------------------------------

namespace dc {

    std::vector<int> neighborhood_node(
        int const& ncols,
        int const& nrows,
        int const& window_size_x,
        int const& window_size_y,
        int const& node_ID)
    {
        std::vector<int> neighborhood_ID(window_size_x * window_size_y);

        std::vector<int> node_ID_x(window_size_x);
        std::vector<int> node_ID_y(window_size_y);

        std::size_t iterations_x = static_cast<std::size_t>(std::round((window_size_x) / 2));
        std::size_t iterations_y = static_cast<std::size_t>(std::round((window_size_y) / 2));

        node_ID_x[0] = 0;

        for (int i = 1; i <= iterations_x; i++)
        {

            int row_num_node = static_cast<int>(std::round(node_ID / ncols));

            /*std::cout << "node_ID: " << node_ID << " i: " << i << " (node_ID - i): " << (node_ID - i)
                      << " row_num_node: " << row_num_node
                      << " (row_num_node * ncols): " << (row_num_node * ncols) << std::endl;*/

            if ((node_ID - i) < (row_num_node * ncols))
            {
                node_ID_x[i] = i;
                node_ID_x[i + iterations_x] =
                    iterations_x + i;  // window_size_x + (-(node_ID - i - (row_num_node * ncols)));
            }
            else if (node_ID + i > (((row_num_node + 1) * ncols) - 1))
            {

                node_ID_x[i] =
                    -iterations_x - i;  //-window_size_x - (node_ID + i - (((row_num_node + 1) * ncols) - 1));
                node_ID_x[i + iterations_x] = -i;
            }
            else
            {

                node_ID_x[i] = i;
                node_ID_x[i + iterations_x] = -i;
            }
        }

        /*std::cout << "node_ID_x: " << std::endl;

        for (int i = 0; i < node_ID_x.size(); ++i)
        {
            std::cout << node_ID_x[i] << " ";
        }

        std::cout << std::endl;*/

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

        return neighborhood_ID;
    }

}  // namespace dc