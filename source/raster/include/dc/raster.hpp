
#ifndef __raster_HPP
#define __raster_HPP
#include <vector>
namespace dc {
    class Raster
    {
        private:

            int size_x;
            int size_y;

        public:

            float noData_value{-88};
            std::vector<float> value;
            Raster(int const input_size_x, int const input_size_y);
            int get_size_x() const
            {
                return size_x;
            }
            int get_size_y() const
            {
                return size_y;
            }
    };
}  // namespace dc
#endif
