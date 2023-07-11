
#ifndef __raster_HPP
#define __raster_HPP

#include <vector> 

namespace dc {

class Raster
{

public:

    int size_x;
    int size_y; 
    std::vector<float> value;

    Raster(int const x=0, int const y=0);  
    ~Raster();
};


} //namespace dc

#endif

