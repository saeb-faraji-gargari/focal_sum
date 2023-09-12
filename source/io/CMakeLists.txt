add_library(io STATIC source/io.cpp)

target_include_directories(io PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(io PUBLIC raster GDAL::GDAL)

