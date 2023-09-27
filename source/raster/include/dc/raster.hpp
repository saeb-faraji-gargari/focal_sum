
#ifndef __raster_HPP
#define __raster_HPP

#include <vector>

namespace dc {

    class Raster
    {

        private:

            int num_x, num_y;

        public:

            int size_x;
            int size_y;
            float noData_value {-88};
            std::vector<float> value;

            Raster(int const num_x, int const num_y);
    };

}  // namespace dc

#endif
