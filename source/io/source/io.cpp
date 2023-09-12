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

    const Raster read(std::string const& input_file)

    {

        GDALDatasetPtr poDataset(static_cast<GDALDataset*>(GDALOpen(input_file.c_str(), GA_ReadOnly)));

        if (!poDataset)
        {
            throw std::runtime_error("Unable to open input file : " + input_file);
        }

        int const ncols = poDataset->GetRasterXSize();
        int const nrows = poDataset->GetRasterYSize();

        Raster input_raster(ncols, nrows);

        double noData = poDataset->GetRasterBand(1)->GetNoDataValue();

        input_raster.noData_value = noData;

        CPLErr result_read = poDataset->GetRasterBand(1)->RasterIO(
            GF_Read, 0, 0, ncols, nrows, input_raster.value.data(), ncols, nrows, GDT_Float32, 0, 0);

        return input_raster;
    }

    void write(Raster const& input_raster, std::string const& output_file)
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

        std::vector<float> input_raster_data = input_raster.value;

        CPLErr result_write = pTiffDS->GetRasterBand(1)->RasterIO(
            GF_Write, 0, 0, ncols, nrows, input_raster_data.data(), ncols, nrows, GDT_Float32, 0, 0);
    }

}  // namespace dc
