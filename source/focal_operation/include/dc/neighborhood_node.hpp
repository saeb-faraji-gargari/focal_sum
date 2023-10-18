
#ifndef NEIGHBORHOOD_NODE_HPP
#define NEIGHBORHOOD_NODE_HPP

#include <vector>

#include <cmath>

namespace dc {

    void neighborhood_internal(
        int const ncols,
        int const window_size_x,
        int const window_size_y,
        std::vector<int>& neighborhood_ID_internal);

    void neighborhood_node(
        int const ncols,
        int const nrows,
        int const window_size_x,
        int const window_size_y,
        int const node_ID,
        std::vector<int>& node_ID_x,
        std::vector<int>& node_ID_y,
        std::vector<int>& neighborhood_ID);

}  // namespace dc

#endif