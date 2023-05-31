
/*------------------------------------------------------
  This function calculate focal sum using a 3*3 window.
-------------------------------------------------------*/

#include <iostream>
// Gdal includes that are needed for this tutorial
#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

#include <string>

#include "focal_sum.h"

#include <memory>  // For std::unique_ptr, std::make_unique

namespace dataCal {
    void focal_sum(std::string& input_file, std::string& output_file)
    {

        // Register all gdal drivers -- load every possible driver gdal has
        GDALAllRegister();
        
        // lets load a "dataset" which is gdal terminology for your data
        GDALDataset* poDataset = static_cast<GDALDataset*>(GDALOpen(input_file.c_str(), GA_ReadOnly));

        // Get width and height of this dataset
        int const ncols = GDALGetRasterXSize(poDataset);
        int const nrows = GDALGetRasterYSize(poDataset);

        ////////GDALDataset *pTiffDS = nullptr;

        GDALDriver* pDriverTIFF = nullptr;
        pDriverTIFF = GetGDALDriverManager()->GetDriverByName("GTiff");

        GDALDataset* pTiffDS = pDriverTIFF->Create(output_file.c_str(), ncols, nrows, 1, GDT_Float32, NULL);

        std::unique_ptr<float> rowNew(new float[ncols]);
        std::unique_ptr<float> rowOld_1(new float[ncols]);
        std::unique_ptr<float> rowOld_main(new float[ncols]);
        std::unique_ptr<float> rowOld_2(new float[ncols]);

        CPLErr result_rowOld_main, result_rowOld_1, result_rowOld_2, result_pTiffDS;

        for (int row = 0; row < nrows; row++)
        {

            CPLErr result_rowOld_main = poDataset->GetRasterBand(1)->RasterIO(
                GF_Read, 0, row, ncols, 1, rowOld_main.get(), ncols, 1, GDT_Float32, 0, 0);

            if (result_rowOld_main != CE_None)
            {
                // Handle the error here, such as logging the error message or taking
                // appropriate action.
            }

            if (row == 0)
            {

                result_rowOld_1 = poDataset->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row + 1, ncols, 1, rowOld_1.get(), ncols, 1, GDT_Float32, 0, 0);
                result_rowOld_2 = poDataset->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row + 2, ncols, 1, rowOld_2.get(), ncols, 1, GDT_Float32, 0, 0);
            }
            else if (row == nrows - 1)
            {

                result_rowOld_1 = poDataset->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row - 1, ncols, 1, rowOld_1.get(), ncols, 1, GDT_Float32, 0, 0);
                result_rowOld_2 = poDataset->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row - 2, ncols, 1, rowOld_2.get(), ncols, 1, GDT_Float32, 0, 0);
            }
            else
            {

                result_rowOld_1 = poDataset->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row - 1, ncols, 1, rowOld_1.get(), ncols, 1, GDT_Float32, 0, 0);
                result_rowOld_2 = poDataset->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row + 1, ncols, 1, rowOld_2.get(), ncols, 1, GDT_Float32, 0, 0);
            }

            if (result_rowOld_1 != CE_None)
            {
                // Handle the error here, such as logging the error message or taking
                // appropriate action.
            }

            if (result_rowOld_2 != CE_None)
            {
                // Handle the error here, such as logging the error message or taking
                // appropriate action.
            }

            for (int col = 0; col < ncols; col++)
            {

                if (col == 0)
                {

                    rowNew.get()[col] =
                        rowOld_main.get()[col + 2] + rowOld_main.get()[col] + rowOld_main.get()[col + 1] +
                        rowOld_1.get()[col + 2] + rowOld_1.get()[col] + rowOld_1.get()[col + 1] +
                        rowOld_2.get()[col + 2] + rowOld_2.get()[col] + rowOld_2.get()[col + 1];
                }

                else if (col == ncols - 1)
                {

                    rowNew.get()[col] =
                        rowOld_main.get()[col - 1] + rowOld_main.get()[col] + rowOld_main.get()[col - 2] +
                        rowOld_1.get()[col - 1] + rowOld_1.get()[col] + rowOld_1.get()[col - 2] +
                        rowOld_2.get()[col - 1] + rowOld_2.get()[col] + rowOld_2.get()[col - 2];
                }
                else
                {

                    rowNew.get()[col] =
                        rowOld_main.get()[col - 1] + rowOld_main.get()[col] + rowOld_main.get()[col + 1] +
                        rowOld_1.get()[col - 1] + rowOld_1.get()[col] + rowOld_1.get()[col + 1] +
                        rowOld_2.get()[col - 1] + rowOld_2.get()[col] + rowOld_2.get()[col + 1];
                }
            }

            result_pTiffDS = pTiffDS->GetRasterBand(1)->RasterIO(
                GF_Write, 0, row, ncols, 1, rowNew.get(), ncols, 1, GDT_Float32, 0, 0);

            if (result_pTiffDS != CE_None)
            {
                // Handle the error here, such as logging the error message or taking
                // appropriate action.
            }
        }

        GDALClose(poDataset);
        GDALClose(pTiffDS);

        GDALDestroyDriverManager();
    }
}  // namespace dataCal
