
#include "dc/raster.hpp"

namespace dc {


    Raster::Raster(int const x, int const y):
        size_x(x),
        size_y(y)
    {

        value.resize(size_x * size_y);
    }

    Raster::~Raster()
    {
    }

}  // namespace dc
