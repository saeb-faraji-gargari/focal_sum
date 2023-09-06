
add_library(raster_operation STATIC source/raster.cpp)

target_include_directories(raster_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# find_package(Doxygen REQUIRED)

# set(DOXYGEN_GENERATE_HTML YES)

# doxygen_add_docs(doc ${PROJECT_SOURCE_DIR})
