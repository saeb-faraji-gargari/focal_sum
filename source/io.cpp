

#include "dc/io.hpp"

#include <iostream>

namespace dc {


    GDALlibrary::GDALlibrary()
    {
        GDALAllRegister();
    }

    GDALlibrary::~GDALlibrary()
    {
        GDALDestroyDriverManager();
    }

    Raster read(std::string const & input_file)

    {
        

        GDALDatasetPtr poDataset(static_cast<GDALDataset*>(GDALOpen(input_file.c_str(), GA_ReadOnly)));

        if (!poDataset)
        {
            std::cout << "Error Unable to open input file :" << input_file;
            return Raster();
        }

        int const ncols = poDataset->GetRasterXSize();
        int const nrows = poDataset->GetRasterYSize();

        Raster input_raster(ncols, nrows);

        std::unique_ptr<float[]> row_value(new float[ncols]);
       

        for (std::size_t i = 0; i < nrows; i++)
        {
            

            CPLErr result_row_value = poDataset->GetRasterBand(1)->RasterIO(
                GF_Read, 0, i, ncols, 1, row_value.get(), ncols, 1, GDT_Float32, 0, 0);

            if (result_row_value == CE_None)
            {
                for (std::size_t j = 0; j < ncols; j++)
                {
                    input_raster.value[(i * ncols) + j] = row_value.get()[j];
                }
            }
            else
            {
                std::cout << "Error GDALRasterIO cannot be called successfully" << std::endl;
            }
        }


        return input_raster;
    }

    void write(Raster & input_raster, std::string const & output_file)
    {

        int const ncols = input_raster.size_x;
        int const nrows = input_raster.size_y;

        std::unique_ptr<float[]> row_value(new float[ncols]);


        GDALDriver* pDriverTIFF = nullptr;
        pDriverTIFF = GetGDALDriverManager()->GetDriverByName("GTiff");

        if (pDriverTIFF == nullptr)
        {
            std::cout << "Error retrieving GDAL driver" << std::endl;
            return;
        }
        
        GDALDatasetPtr pTiffDS(pDriverTIFF->Create(output_file.c_str(), ncols, nrows, 1, GDT_Float32, nullptr));


        if (pTiffDS == nullptr)
        {
            std::cout << "Error creating dataset" << std::endl;
            return;
        }


        for (std::size_t i = 0; i < nrows; i++)
        {
            for (std::size_t j = 0; j < ncols; j++)
            {
                row_value[j] = input_raster.value[(i * ncols) + j];
            }

            

            CPLErr result_row_value = pTiffDS->GetRasterBand(1)->RasterIO(
                GF_Write, 0, i, ncols, 1, row_value.get(), ncols, 1, GDT_Float32, 0, 0);

            if (result_row_value == !CE_None)
            {

                std::cout << " Error in GDALRasterIO write " << std::endl;
            }
        }

    }

}  // namespace dc
