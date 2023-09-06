
#include "dc/raster.hpp"

namespace dc {

    Raster::Raster(int const num_x, int const num_y):
        size_x{num_x},
        size_y{num_y}

    {

        value.resize(num_x * num_y);
    }

}  // namespace dc
