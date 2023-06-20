#ifndef __FOCAL_SUM_H__
#define __FOCAL_SUM_H__

#include <iostream>

#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

#include <string>

#include <memory>  // For std::unique_ptr, std::make_unique

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

    using Raster_data = std::unique_ptr<::GDALDataset, GDALDatasetDeleter>;

    Raster_data read(std::string& input_file);

    Raster_data focal_sum(Raster_data& input_file, std::string&);

    void write(Raster_data& input_MEM, std::string& output_file);

}  // namespace dc

#endif
