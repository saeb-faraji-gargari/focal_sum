cmake_minimum_required(VERSION 3.5)

project(focal_sum)

# ##############################################################################
# Create an executable
# ##############################################################################

add_executable(${PROJECT_NAME} src/main.cpp)

# ##############################################################################
# Create a library
# ##############################################################################

add_library(focal_sum_operation STATIC src/focal_sum.cpp src/data_set.cpp)

target_include_directories(focal_sum_operation PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Find system installed GDAL package with predefined CMake variable for finding GDAL
find_package(GDAL REQUIRED)

# Find Boost package with required components
find_package(
  Boost 1.40
  COMPONENTS program_options
  REQUIRED)

# Specify location of GDAL header files
include_directories(
  ${GDAL_INCLUDE_DIRS}
)

# Specify GDAL libraries to link your cpp executable target against
target_link_libraries(${PROJECT_NAME} focal_sum_operation ${GDAL_LIBRARIES}
                      ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_LIBRARIES})

# Enable testing functionality
enable_testing()

# Create a testing binary
add_executable(focal_sum_test src/test.cpp)

# Define tests
add_test(NAME test_add COMMAND $<TARGET_FILE:focal_sum_test>)

#----------------------------------------------------------------------------

#     set(PROJECT_VERSION 1.0.0)

# Include the GNUInstallDirs module
include(GNUInstallDirs)

# Install the executable, library, and header files
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(TARGETS focal_sum_operation DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES include/focal_sum.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Specify the test directory
set(CMAKE_INSTALL_TESTDIR ${CMAKE_INSTALL_PREFIX}/test)
# Install the test executable to the test directory
install(TARGETS focal_sum_test DESTINATION ${CMAKE_INSTALL_TESTDIR})

#---------------ravesh dovom----------------------------------------------------------------------------------------

##***********  dar in ravesh set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install) dakhele cmake anjam shode va niyazi be run dastor zir dar terminal va foldere build nist
##*cmake -DCMAKE_INSTALL_PREFIX=~/focal_sum_project/test_GDAL_and_command_line_argument/20230605_focal_sum_rev3/install ..
##nist akbate engar in khob nist ba behtare cmake -DCMAKE_INSTALL_PREFIX= be shorate dasti dar terminal anjam beshe ta cmake file

#***********


######*set(CMAKE_INSTALL_PREFIX ~/focal_sum_project/test_GDAL_and_command_line_argument/20230605_focal_sum_rev3/install)
#set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)



#install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
#install(TARGETS _focal_sum DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
#install(FILES include/focal_sum.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

#-----------------------End: ravesh dovom---------------------------------


find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doc)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doc)

set(DOXYGEN_CONFIG_FILE ${DOXYGEN_INPUT_DIR}/Doxyfile)

# Create a custom target for generating Doxygen documentation
add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG_FILE}
    WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR}
    COMMENT "Generating Doxygen documentation"
)





