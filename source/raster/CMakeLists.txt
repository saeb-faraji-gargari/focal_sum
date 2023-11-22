
add_library(raster STATIC source/raster.cpp)

target_include_directories(raster PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



