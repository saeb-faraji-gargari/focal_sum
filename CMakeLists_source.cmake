cmake_minimum_required(VERSION 3.14)

project(focal_project LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

find_package(
    Boost 1.40
    COMPONENTS program_options
    REQUIRED
)

add_executable(focal_sum app_focal_sum/source/main.cpp)

add_executable(focal_mean app_focal_mean/source/main.cpp)

add_library(io_operation STATIC lib_IO/source/io.cpp)

add_library(raster_operation STATIC lib_raster/source/raster.cpp)

add_library(focal_sum_operation STATIC lib_focal_sum/source/focal_sum.cpp)

add_library(focal_mean_operation STATIC lib_focal_mean/source/focal_mean.cpp)

target_include_directories(io_operation PUBLIC ${PROJECT_SOURCE_DIR}/lib_IO/include)

target_include_directories(raster_operation PUBLIC ${PROJECT_SOURCE_DIR}/lib_raster/include)

target_include_directories(focal_sum_operation PUBLIC ${PROJECT_SOURCE_DIR}/lib_focal_sum/include)

add_library(neighborhood_operation STATIC lib_neighborhood_node/source/neighborhood_node.cpp)
target_include_directories(
    neighborhood_operation PUBLIC ${PROJECT_SOURCE_DIR}/lib_neighborhood_node/include
)

target_include_directories(focal_mean_operation PUBLIC ${PROJECT_SOURCE_DIR}/lib_focal_mean/include)

find_package(GDAL REQUIRED)

target_link_libraries(io_operation PUBLIC raster_operation GDAL::GDAL)

target_link_libraries(focal_sum_operation PUBLIC raster_operation neighborhood_operation)

target_link_libraries(focal_mean_operation PUBLIC focal_sum_operation raster_operation)

target_link_libraries(
    focal_sum PRIVATE io_operation focal_sum_operation Boost::boost Boost::program_options
)

target_link_libraries(
    focal_mean PRIVATE io_operation focal_mean_operation Boost::boost Boost::program_options
)

enable_testing()

add_executable(focal_sum_app_test app_focal_sum/test/test.cpp)

add_test(NAME test_focal_sum_app COMMAND $<TARGET_FILE:focal_sum_app_test>)

add_executable(neighborhood_test lib_neighborhood_node/test/test_neighborhood_node.cpp)
target_link_libraries(neighborhood_test PUBLIC neighborhood_operation)
add_test(NAME test_neighborhood_node COMMAND neighborhood_test)

add_executable(focal_sum_test lib_focal_sum/test/test_focal_sum.cpp)
target_link_libraries(focal_sum_test PUBLIC focal_sum_operation)
add_test(NAME test_focal_sum COMMAND focal_sum_test)

include(GNUInstallDirs)

install(TARGETS focal_sum DESTINATION ${CMAKE_INSTALL_BINDIR})

find_package(Doxygen REQUIRED)

set(DOXYGEN_GENERATE_HTML YES)

doxygen_add_docs(doc ${PROJECT_SOURCE_DIR})
