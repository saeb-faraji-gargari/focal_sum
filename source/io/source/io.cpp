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

    std::string read_set_data_type(std::string const& input_file)
    {
        GDALDatasetPtr poDataset(static_cast<GDALDataset*>(GDALOpen(input_file.c_str(), GA_ReadOnly)));

        // Get the first raster band
        GDALRasterBandH poBand = GDALGetRasterBand(poDataset.get(), 1);
        // Get the data type of the band
        GDALDataType gdalDataType = GDALGetRasterDataType(poBand);

        switch (gdalDataType)
        {
            case GDT_Byte:
                return "GDT_Byte";
            case GDT_UInt16:
                return "GDT_UInt16";
            case GDT_Int16:
                return "GDT_Int16";
            case GDT_UInt32:
                return "GDT_UInt32";
            case GDT_Int32:
                return "GDT_Int32";
            case GDT_Float32:
                return "GDT_Float32";
            case GDT_Float64:
                return "GDT_Float64";
            default:
                return "data_type_unknown";
        }
    }

}  // namespace dc
