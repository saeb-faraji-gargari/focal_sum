add_library(io_operation STATIC source/io.cpp)

target_include_directories(io_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(GDAL REQUIRED)

target_link_libraries(io_operation PUBLIC raster_operation GDAL::GDAL)

# find_package(Doxygen REQUIRED)

# set(DOXYGEN_GENERATE_HTML YES)

# doxygen_add_docs(doc ${PROJECT_SOURCE_DIR})
