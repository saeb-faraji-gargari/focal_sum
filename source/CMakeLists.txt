find_package(
    Boost 1.40
    COMPONENTS program_options
    REQUIRED
)

add_subdirectory(raster)
add_subdirectory(IO)
add_subdirectory(focal_operation)

add_executable(focal_sum focal_operation/source/main_sum.cpp)
add_executable(focal_mean focal_operation/source/main_mean.cpp)

target_link_libraries(focal_sum_operation PUBLIC raster_operation neighborhood_operation)

target_link_libraries(focal_mean_operation PUBLIC focal_sum_operation raster_operation)

target_link_libraries(
    focal_sum PRIVATE io_operation focal_sum_operation Boost::boost Boost::program_options
)

target_link_libraries(
    focal_mean PRIVATE io_operation focal_mean_operation Boost::boost Boost::program_options
)

add_executable(main_sum_test focal_operation/test/test_main_sum.cpp)
add_test(NAME test_focal_sum_app COMMAND $<TARGET_FILE:main_sum_test>)
