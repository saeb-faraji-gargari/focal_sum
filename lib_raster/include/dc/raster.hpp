
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
            double noData_value;
            std::vector<float> value;

            Raster(int const num_x, int const num_y);
    };

}  // namespace dc

#endif
