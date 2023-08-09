#include "dc/focal_mean.hpp"

namespace dc {

    const Raster focal_mean(Raster const& input)

    {

        const Raster sum = focal_sum(input);
        Raster mean(sum.size_x, sum.size_y);

        for (std::size_t i = 0; i < (sum.size_y * sum.size_x); i++)

        {

            mean.value[i] = sum.value[i] / 9;
        }

        return mean;
    }

}  // namespace dc