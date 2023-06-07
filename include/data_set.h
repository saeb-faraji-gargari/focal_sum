#ifndef __DATA_SET_H__
#define __DATA_SET_H__


#include <gdal.h>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>


namespace data_set {
    GDALDataset* read(std::string& input_file);
	//void read(std::string& input_file);
}

#endif
