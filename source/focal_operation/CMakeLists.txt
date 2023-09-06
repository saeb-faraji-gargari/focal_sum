add_library(focal_sum_operation STATIC source/focal_sum.cpp)

add_library(focal_mean_operation STATIC source/focal_mean.cpp)

add_library(neighborhood_operation STATIC source/neighborhood_node.cpp)

target_include_directories(focal_sum_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(focal_mean_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(neighborhood_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)

find_package(
    Boost 1.40
    COMPONENTS program_options
    REQUIRED
)

add_subdirectory(../raster raster_build)
add_subdirectory(../IO IO_build)

add_executable(focal_sum source/main_sum.cpp)
add_executable(focal_mean source/main_mean.cpp)

target_link_libraries(focal_sum_operation PUBLIC raster_operation neighborhood_operation)

target_link_libraries(focal_mean_operation PUBLIC focal_sum_operation raster_operation)

target_link_libraries(
    focal_sum PRIVATE io_operation focal_sum_operation Boost::boost Boost::program_options
)

target_link_libraries(
    focal_mean PRIVATE io_operation focal_mean_operation Boost::boost Boost::program_options
)

add_executable(main_sum_test test/test_main_sum.cpp)
add_test(NAME test_focal_sum_app COMMAND $<TARGET_FILE:main_sum_test>)
