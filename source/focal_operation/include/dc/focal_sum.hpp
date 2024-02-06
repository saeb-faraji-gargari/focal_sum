#pragma once

#include "dc/raster.hpp"

namespace dc {

    Raster focal_sum(Raster const& input, int const window_size);

}  // namespace dc
