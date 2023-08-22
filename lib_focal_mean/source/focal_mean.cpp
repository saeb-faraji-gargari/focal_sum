#include "dc/focal_mean.hpp"

namespace dc {

    const Raster focal_mean(Raster const& input, int const& window_size_x, int const& window_size_y)

    {

        const Raster sum = focal_sum(input, window_size_x, window_size_y);

        Raster mean(sum.size_x, sum.size_y);

        for (std::size_t i = 0; i < (sum.size_y * sum.size_x); i++)

        {

            mean.value[i] = sum.value[i] / (window_size_x * window_size_y);
        }

        return mean;
    }

}  // namespace dc