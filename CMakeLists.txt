cmake_minimum_required(VERSION 3.14)

project(focal_sum LANGUAGES CXX)

find_package(
    Boost 1.40
    COMPONENTS program_options
    REQUIRED
)

add_executable(focal_sum source/main.cpp)

set_target_properties(focal_sum PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(io_operation STATIC source/io.cpp source/raster.cpp)

add_library(focal_sum_operation STATIC source/focal_sum.cpp)

target_include_directories(io_operation PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_include_directories(focal_sum_operation PUBLIC ${PROJECT_SOURCE_DIR}/include)

set_target_properties(
    io_operation focal_sum_operation PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)


find_package(GDAL REQUIRED)

target_link_libraries(io_operation PUBLIC GDAL::GDAL)

target_link_libraries(
    focal_sum PRIVATE io_operation focal_sum_operation Boost::boost Boost::program_options
)

enable_testing()

add_executable(focal_sum_test source/test.cpp)

set_target_properties(focal_sum_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_test(NAME test_add COMMAND $<TARGET_FILE:focal_sum_test>)

include(GNUInstallDirs)

install(TARGETS focal_sum DESTINATION ${CMAKE_INSTALL_BINDIR})

find_package(Doxygen REQUIRED)

set(DOXYGEN_GENERATE_HTML YES)

doxygen_add_docs(doc ${PROJECT_SOURCE_DIR})
