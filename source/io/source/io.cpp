#include "dc/io.hpp"
#include <iostream>

namespace dc {

    GDALLibrary::GDALLibrary()
    {
        GDALAllRegister();
    }

    GDALLibrary::~GDALLibrary()
    {
        GDALDestroyDriverManager();
    }

    Raster read(std::string const& input_data_name)

    {

        GDALDatasetPtr poDataset(static_cast<GDALDataset*>(GDALOpen(input_data_name.c_str(), GA_ReadOnly)));

        if (!poDataset)
        {
            throw std::runtime_error("Unable to open input file : " + input_data_name);
        }

        int const ncols = poDataset->GetRasterXSize();
        int const nrows = poDataset->GetRasterYSize();

        float noData = poDataset->GetRasterBand(1)->GetNoDataValue();

        Raster input_raster(ncols, nrows);
        input_raster.noData_value = noData;

        CPLErr result_read = poDataset->GetRasterBand(1)->RasterIO(
            GF_Read, 0, 0, ncols, nrows, input_raster.value.data(), ncols, nrows, GDT_Float32, 0, 0);

        return input_raster;
    }

    void write(Raster const& input_raster, std::string const& output_data_name)
    {

        int const ncols = input_raster.get_size_x();
        int const nrows = input_raster.get_size_y();

        GDALDriver* pDriverTIFF = nullptr;
        pDriverTIFF = GetGDALDriverManager()->GetDriverByName("GTiff");

        GDALDatasetPtr pTiffDS(
            pDriverTIFF->Create(output_data_name.c_str(), ncols, nrows, 1, GDT_Float32, nullptr));

        if (pTiffDS == nullptr)
        {
            throw std::runtime_error("Unable to open output file to write : " + output_data_name);
        }

        // std::vector<float>& input_raster_data = input_raster.value;
        std::vector<float> input_raster_data = std::move(input_raster.value);

        CPLErr result_write = pTiffDS->GetRasterBand(1)->RasterIO(
            GF_Write, 0, 0, ncols, nrows, input_raster_data.data(), ncols, nrows, GDT_Float32, 0, 0);
    }

}  // namespace dc
