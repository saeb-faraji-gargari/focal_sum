
#ifndef __raster_HPP
#define __raster_HPP

#include <vector>

namespace dc {

    class Raster
    {

        private:

            int num_x1, num_y1;

        public:

            int size_x;
            int size_y;
            std::vector<float> value;

            Raster(int const num_x, int const num_y);
    };

}  // namespace dc

#endif
