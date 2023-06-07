
/*------------------------------------------------------
  This function calculate focal sum using a 3*3 window.
-------------------------------------------------------*/

#include <iostream>
// Gdal includes that are needed for this tutorial
#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

#include <string>

#include "data_set.h"

#include <memory> // For std::unique_ptr, std::make_unique

namespace data_set {


GDALDataset *read(std::string &input_file)

// void read(std::string& input_file)
{

  // Register all gdal drivers -- load every possible driver gdal has
  GDALAllRegister();
  // Lets open a Tif

  // lets load a "dataset" which is gdal terminology for your data

  GDALDataset *poDataset =
      static_cast<GDALDataset *>(GDALOpen(input_file.c_str(), GA_ReadOnly));

  return poDataset;
}

} // namespace data_set
