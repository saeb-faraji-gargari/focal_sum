cmake_minimum_required(VERSION 3.5)

project(focal_sum LANGUAGES CXX)

# ##################################################################################################
# Create an executable
# ##################################################################################################

add_executable(${PROJECT_NAME} source/main.cpp)

# ##################################################################################################
# Create a library
# ##################################################################################################

add_library(focal_sum_operation STATIC source/focal_sum.cpp)

target_include_directories(focal_sum_operation PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Find system installed GDAL package with predefined CMake variable for finding GDAL
find_package(GDAL REQUIRED)
# find_package(GDAL CONFIG REQUIRED)

# Specify location of GDAL header files include_directories(
target_include_directories(focal_sum_operation PRIVATE ${GDAL_INCLUDE_DIRS})

target_link_libraries(
    ${PROJECT_NAME} PRIVATE GDAL::GDAL focal_sum_operation Boost::boost Boost::program_options
)

# Find Boost package with required components
find_package(
    Boost 1.40
    COMPONENTS program_options
    REQUIRED
)

# Enable testing functionality
enable_testing()

# Create a testing binary
add_executable(focal_sum_test source/test.cpp)

# Define tests
add_test(NAME test_add COMMAND $<TARGET_FILE:focal_sum_test>)

# ----------------------------------------------------------------------------

# Include the GNUInstallDirs module
include(GNUInstallDirs)

# Install the executable, library, and header files
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS focal_sum_operation DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Find Doxygen package
find_package(Doxygen REQUIRED)

set(DOXYGEN_GENERATE_HTML YES)

doxygen_add_docs(doc ${PROJECT_SOURCE_DIR})
