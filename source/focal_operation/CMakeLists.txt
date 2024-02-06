add_library(focal_operation STATIC source/focal_sum.cpp
                                   source/neighborhood_node.cpp)

target_include_directories(focal_operation
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_include_directories(focal_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../lib_mdspan)

# Find mdspan, and fetch if not found
find_package(mdspan QUIET)

if (NOT mdspan_FOUND)
  message(STATUS "No installed mdspan found, fetching from Github")

  # Include the FetchContent module
  include(FetchContent)

  # Declare and fetch mdspan as an external project
  FetchContent_Declare(
    mdspan
    GIT_REPOSITORY https://github.com/kokkos/mdspan.git
    GIT_TAG        stable
  )

  # Fetch and populate mdspan
  FetchContent_GetProperties(mdspan)
  if(NOT mdspan_POPULATED)
    FetchContent_Populate(mdspan)
    add_subdirectory(${mdspan_SOURCE_DIR} ${mdspan_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()

  # Make mdspan available for use in the project
  FetchContent_MakeAvailable(mdspan)

  message(STATUS "fetch mdspan_SOURCE_DIR: ${mdspan_SOURCE_DIR}")
  message(STATUS "fetch mdspan_BINARY_DIR: ${mdspan_BINARY_DIR}")

endif()


# Now that mdspan is available, get its location
get_target_property(_location mdspan LOCATION)
message(STATUS "Location of mdspan: ${_location}")


target_include_directories(focal_operation PUBLIC ${mdspan_SOURCE_DIR}/include/mdspan)

target_link_libraries(focal_operation PUBLIC raster mdspan)

#target_include_directories(focal_operation PUBLIC ${mdspan_SOURCE_DIR}/include)


add_executable(focal_sum source/main_sum.cpp)
#add_executable(focal_mean source/main_mean.cpp)
#add_executable(focal_min source/main_min.cpp)

#target_compile_options(focal_operation PRIVATE -pg)

target_link_libraries(focal_sum PRIVATE io focal_operation Boost::boost
                                        Boost::program_options)

#target_compile_options(focal_sum PRIVATE -pg)


#target_link_libraries(focal_mean PRIVATE io focal_operation Boost::boost
#                                         Boost::program_options)

#target_link_libraries(focal_min PRIVATE io focal_operation Boost::boost
#                                         Boost::program_options)

add_subdirectory(test)
