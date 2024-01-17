
#include "dc/raster.hpp"
namespace dc {
    Raster::Raster(int const input_size_x, int const input_size_y):
        size_x(input_size_x),
        size_y(input_size_y),
        value(input_size_x * input_size_y, 0.0f)
    {
    }
}  // namespace dc
