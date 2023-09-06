#include "dc/focal_sum.hpp"
#include "dc/raster.hpp"
#include <vector> 
#include <iostream>

#include <limits> 


int test_1() {

const int ncols=3;
const int nrows=4;

dc::Raster input_raster(ncols, nrows);

float noData = std::numeric_limits<float>::quiet_NaN(); 

std::vector<float> input_value_vactor = {
        1.1, 2.2, 3.3, 4.4,
        5.5, 6.6, 7.7, 8.8,
        9.9, 10.1, 11.11, 12.12
    };


input_raster.value=input_value_vactor;


std::vector<float> output_value_vactor = {
        57.51, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };


const dc::Raster output = dc::focal_sum(input_raster);

if (output.value==output_value_vactor)
{
    return 0;
}
else 
{

return 1;

}


}

int test_2() {

const int ncols=3;
const int nrows=4;

dc::Raster input_raster(ncols, nrows);

float noData = std::numeric_limits<float>::quiet_NaN(); 

std::vector<float> input_value_vactor = {
        1.1, 2.2, noData, 4.4,
        5.5, 6.6, 7.7, 8.8,
        9.9, 10.1, 11.11, noData
    };



input_raster.value=input_value_vactor;


std::vector<float> output_value_vactor = {
        noData, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };


const dc::Raster output = dc::focal_sum(input_raster);

if (output.value==output_value_vactor)
{
    return 0;
}
else 
{

return 1;

}


}

int main() 
{


int test_1_status = test_1();

if (test_1_status)
{
std::cout << "test_1 is passed";
}
else 
{
std::cout << "test_1 is failed";
}


}