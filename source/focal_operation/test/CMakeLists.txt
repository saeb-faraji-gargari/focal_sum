
add_executable(neighborhood_test test_neighborhood_node.cpp)
target_link_libraries(neighborhood_test PRIVATE Boost::unit_test_framework focal_operation)
add_test(NAME test_neighborhood_node COMMAND neighborhood_test)

#add_executable(focal_sum_test test_focal_sum.cpp)
#target_link_libraries(focal_sum_test PRIVATE Boost::unit_test_framework focal_operation)
#add_test(NAME test_focal_sum COMMAND focal_sum_test)
