
#include "focal_sum.h"

namespace dc {

    Raster_data read(std::string& input_file)
    {

        // Register all gdal drivers -- load every possible driver gdal has
        GDALAllRegister();

        Raster_data poDataset(static_cast<GDALDataset*>(GDALOpen(input_file.c_str(), GA_ReadOnly)));

        if (!poDataset)
        {

            return Raster_data(nullptr);
        }

        return poDataset;
    }

    void write(Raster_data& input_MEM, std::string& output_file)
    {

        int const ncols = input_MEM->GetRasterXSize();
        int const nrows = input_MEM->GetRasterYSize();

        GDALDriver* pDriverTIFF = nullptr;
        pDriverTIFF = GetGDALDriverManager()->GetDriverByName("GTiff");

        Raster_data pTiffDS(pDriverTIFF->Create(output_file.c_str(), ncols, nrows, 1, GDT_Float32, nullptr));

        std::unique_ptr<float> read_row(new float[ncols]);

        for (int row = 0; row < nrows; row++)
        {

            CPLErr result_row_input_MEM = input_MEM->GetRasterBand(1)->RasterIO(
                GF_Read, 0, row, ncols, 1, read_row.get(), ncols, 1, GDT_Float32, 0, 0);

            if (result_row_input_MEM != CE_None)
            {
                // Handle the error here, such as logging the error message or
                // taking appropriate action.
            }

            CPLErr result_pTiffDS = pTiffDS->GetRasterBand(1)->RasterIO(
                GF_Write, 0, row, ncols, 1, read_row.get(), ncols, 1, GDT_Float32, 0, 0);

            if (result_pTiffDS != CE_None)
            {
                // Handle the error here, such as logging the error message or
                // taking appropriate action.
            }
        }
    }

    /**
     * ------------------------------------------------------
     * This function calculate focal sum using a 3*3 window.
     * -------------------------------------------------------
     */

    Raster_data focal_sum(Raster_data& input_raster, std::string& output_file)
    {

        int const ncols = input_raster->GetRasterXSize();
        int const nrows = input_raster->GetRasterYSize();

        GDALDriver* pDriverTIFF = nullptr;
        pDriverTIFF = GetGDALDriverManager()->GetDriverByName("GTiff");

        Raster_data pTiffDS(pDriverTIFF->Create(output_file.c_str(), ncols, nrows, 1, GDT_Float32, nullptr));

        Raster_data pTiffDS_MEM(GetGDALDriverManager()->GetDriverByName("MEM")->Create(
            "",
            ncols,
            nrows,
            1,
            GDT_Float32,
            nullptr));  // ok chon constructer initilize mishavad

        std::unique_ptr<float> rowNew(new float[ncols]);
        std::unique_ptr<float> rowOld_1(new float[ncols]);
        std::unique_ptr<float> rowOld_main(new float[ncols]);
        std::unique_ptr<float> rowOld_2(new float[ncols]);

        CPLErr result_rowOld_main, result_rowOld_1, result_rowOld_2, result_pTiffDS, result_pTiffDS_MEM;

        for (int row = 0; row < nrows; row++)
        {

            result_rowOld_main = input_raster->GetRasterBand(1)->RasterIO(
                GF_Read, 0, row, ncols, 1, rowOld_main.get(), ncols, 1, GDT_Float32, 0, 0);

            if (result_rowOld_main != CE_None)
            {
                // Handle the error here, such as logging the error message or
                // taking appropriate action.
            }

            if (row == 0)
            {

                result_rowOld_1 = input_raster->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row + 1, ncols, 1, rowOld_1.get(), ncols, 1, GDT_Float32, 0, 0);
                result_rowOld_2 = input_raster->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row + 2, ncols, 1, rowOld_2.get(), ncols, 1, GDT_Float32, 0, 0);
            }
            else if (row == nrows - 1)
            {

                result_rowOld_1 = input_raster->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row - 1, ncols, 1, rowOld_1.get(), ncols, 1, GDT_Float32, 0, 0);
                result_rowOld_2 = input_raster->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row - 2, ncols, 1, rowOld_2.get(), ncols, 1, GDT_Float32, 0, 0);
            }
            else
            {

                result_rowOld_1 = input_raster->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row - 1, ncols, 1, rowOld_1.get(), ncols, 1, GDT_Float32, 0, 0);
                result_rowOld_2 = input_raster->GetRasterBand(1)->RasterIO(
                    GF_Read, 0, row + 1, ncols, 1, rowOld_2.get(), ncols, 1, GDT_Float32, 0, 0);
            }

            if (result_rowOld_1 != CE_None)
            {
                // Handle the error here, such as logging the error message or
                // taking appropriate action.
            }

            if (result_rowOld_2 != CE_None)
            {
                // Handle the error here, such as logging the error message or
                // taking appropriate action.
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
                // Handle the error here, such as logging the error message or
                // taking appropriate action.
            }

            result_pTiffDS_MEM = pTiffDS_MEM->GetRasterBand(1)->RasterIO(
                GF_Write, 0, row, ncols, 1, rowNew.get(), ncols, 1, GDT_Float32, 0, 0);

            if (result_pTiffDS_MEM != CE_None)
            {
                // Handle the error here, such as logging the error message or
                // taking appropriate action.
            }
        }

        GDALDestroyDriverManager();

        return pTiffDS_MEM;
    }

}  // namespace dc
