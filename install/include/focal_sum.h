#ifndef __FOCAL_SUM_H__
#define __FOCAL_SUM_H__


#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>


namespace dc {
    void focal_sum(std::string& input_file, std::string& output_file);
}

#endif
