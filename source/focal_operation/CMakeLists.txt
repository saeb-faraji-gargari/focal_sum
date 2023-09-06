add_library(focal_sum_operation STATIC source/focal_sum.cpp)

add_library(focal_mean_operation STATIC source/focal_mean.cpp)

add_library(neighborhood_operation STATIC source/neighborhood_node.cpp)

target_include_directories(focal_sum_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(focal_mean_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(neighborhood_operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)
