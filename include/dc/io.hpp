
#ifndef __io_HPP
#define __io_HPP


#include <gdal.h>
#include <gdal_priv.h>
//#include <ogrsf_frmts.h>

#include "raster.hpp" 

namespace dc {

 
 struct GDALDatasetDeleter
    {
            void operator()(::GDALDataset* dataset) const
            {
                if (dataset != nullptr)
                {
                    ::GDALClose(dataset);
                }
            }
    };

using GDALDatasetPtr = std::unique_ptr<GDALDataset, GDALDatasetDeleter>;   

class GDALlibrary
{

public:

    GDALlibrary();
    ~GDALlibrary();
};

 Raster read(std::string const &);
 void write(Raster &, std::string const &);

} //namespace dc

#endif

