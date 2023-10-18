add_library(focal_operation STATIC source/focal_sum.cpp
                                   source/neighborhood_node.cpp)

target_include_directories(focal_operation
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(focal_operation PUBLIC raster)

add_executable(focal_sum source/main_sum.cpp)
#add_executable(focal_mean source/main_mean.cpp)
#add_executable(focal_min source/main_min.cpp)

#target_compile_options(focal_operation PRIVATE -pg)

target_link_libraries(focal_sum PRIVATE io focal_operation Boost::boost
                                        Boost::program_options)
										
target_compile_options(focal_sum PRIVATE -pg)


#target_link_libraries(focal_mean PRIVATE io focal_operation Boost::boost
#                                         Boost::program_options)
										 
#target_link_libraries(focal_min PRIVATE io focal_operation Boost::boost
#                                         Boost::program_options)

add_subdirectory(test)
