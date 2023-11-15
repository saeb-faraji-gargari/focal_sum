cmake_minimum_required(VERSION 3.14)

project(focal_project LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# set optimization flag
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")


find_package(Boost 1.40 REQUIRED COMPONENTS program_options unit_test_framework)
find_package(GDAL REQUIRED)
find_package(Doxygen REQUIRED)


enable_testing()

add_subdirectory(source)

include(GNUInstallDirs)

install(TARGETS focal_sum DESTINATION ${CMAKE_INSTALL_BINDIR})

set(DOXYGEN_GENERATE_HTML YES)
doxygen_add_docs(doc ${PROJECT_SOURCE_DIR})

# Add the -pg flag to the compiler options
add_compile_options(-pg)

