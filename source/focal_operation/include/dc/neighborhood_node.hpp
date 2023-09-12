
#ifndef NEIGHBORHOOD_NODE_HPP
#define NEIGHBORHOOD_NODE_HPP

#include <vector>

#include <cmath>

namespace dc {

    std::vector<int> neighborhood_node(int const ncols,
                                       int const nrows,
                                       int const window_size_x,
                                       int const window_size_y,
                                       int const node_ID);

}

#endif