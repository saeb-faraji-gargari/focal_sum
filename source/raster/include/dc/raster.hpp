
#ifndef __raster_HPP
#define __raster_HPP

#include <vector>

namespace dc {
    
    template <typename T>
    class Raster
    {

        private:

            int num_x, num_y;

        public:

            int size_x;
            int size_y;
            T noData_value {-88};
            std::vector<T> value;
            
            Raster(int const num_x, int const num_y);
    };


    template <typename T>
    Raster<T>::Raster(int const num_x, int const num_y):
        size_x{num_x},
        size_y{num_y}

    {

        value.resize(num_x * num_y);
    }
    

}  // namespace dc

#endif
