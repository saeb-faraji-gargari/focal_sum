#ifndef __FOCAL_MEAN_HPP
#define __FOCAL_MEAN_HPP
#include "dc/focal_sum.hpp"
#include "dc/raster.hpp"
namespace dc {
    const Raster focal_mean(Raster const&, int const& window_size_x, int const& window_size_y);
}
#endif