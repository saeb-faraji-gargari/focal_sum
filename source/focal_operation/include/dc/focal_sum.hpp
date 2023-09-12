#ifndef __FOCAL_SUM_HPP
#define __FOCAL_SUM_HPP

#include "dc/raster.hpp"

namespace dc {

    const Raster focal_sum(Raster const& input, int const window_size_x, int const window_size_y);

}  // namespace dc

#endif
