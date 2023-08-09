#ifndef __io_HPP
#define __io_HPP

#include <gdal.h>
#include <gdal_priv.h>
//#include <ogrsf_frmts.h>

#include "dc/raster.hpp"

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

    class GDALLibrary
    {

        public:

            GDALLibrary();
            ~GDALLibrary();
    };

    const Raster read(std::string const&);
    void write(Raster const&, std::string const&);

}  // namespace dc

#endif
