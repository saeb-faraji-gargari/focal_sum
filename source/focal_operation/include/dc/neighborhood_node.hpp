#pragma once

#include <vector>

#include <cmath>

namespace dc {

    void internal_ID(
        int const ncols,
        int const nrows,
        int const window_size_x,
        int const window_size_y,
        std::vector<int>& internal_ID_vectro);

    void internal_external_ID(
        int const ncols,
        int const nrows,
        int const window_size_x,
        int const window_size_y,
        std::vector<int>& internal_ID_vectro,
        std::vector<int>& external_ID_vectro);

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
