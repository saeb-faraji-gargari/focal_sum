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

    Raster read(std::string const& input_data_name);
    void write(Raster const& input_raster, std::string const& output_data_name);

}  // namespace dc

#endif
