#ifndef __io_HPP
#define __io_HPP

#include <gdal.h>
#include <gdal_priv.h>
//#include <ogrsf_frmts.h>

#include "dc/raster.hpp"

namespace dc {

    class GDALLibrary
    {

        public:

            GDALLibrary();
            ~GDALLibrary();
    };

    /*template<typename T>
    Raster<T> read(std::string const&);

    template<typename T>
    void write(Raster<T> const&, std::string const&);*/


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
    
    std::string read_set_data_type(std::string const& input_file);

    template<typename T_value, GDALDataType T_gdalDataType>
    Raster<T_value> read_set_value(std::string const& input_file)
    {

        GDALDatasetPtr poDataset(static_cast<GDALDataset*>(GDALOpen(input_file.c_str(), GA_ReadOnly)));

        if (!poDataset)
        {
            throw std::runtime_error("Unable to open input file : " + input_file);
        }

        int const ncols = poDataset->GetRasterXSize();
        int const nrows = poDataset->GetRasterYSize();

        T_value noData = poDataset->GetRasterBand(1)->GetNoDataValue();

        Raster<T_value> input_raster(ncols, nrows);
        input_raster.noData_value = noData;

        CPLErr result_read = poDataset->GetRasterBand(1)->RasterIO(
            GF_Read, 0, 0, ncols, nrows, input_raster.value.data(), ncols, nrows, T_gdalDataType, 0, 0);

        return input_raster;
    }

    template<typename T>
    void write(Raster<T> const& input_raster, std::string const& output_file)
    {

        int const ncols = input_raster.size_x;
        int const nrows = input_raster.size_y;

        GDALDriver* pDriverTIFF = nullptr;
        pDriverTIFF = GetGDALDriverManager()->GetDriverByName("GTiff");

        GDALDatasetPtr pTiffDS(
            pDriverTIFF->Create(output_file.c_str(), ncols, nrows, 1, GDT_Float32, nullptr));

        if (pTiffDS == nullptr)
        {
            throw std::runtime_error("Unable to open output file to write : " + output_file);
        }

        std::vector<T> input_raster_data = input_raster.value;

        CPLErr result_write = pTiffDS->GetRasterBand(1)->RasterIO(
            GF_Write, 0, 0, ncols, nrows, input_raster_data.data(), ncols, nrows, GDT_Float32, 0, 0);
    }


}  // namespace dc

#endif
