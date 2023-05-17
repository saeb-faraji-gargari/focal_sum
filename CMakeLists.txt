cmake_minimum_required(VERSION 3.5)

project(focal_sum)   


############################################################
# Create an executable
############################################################

add_executable(${PROJECT_NAME}   

	src/main.cpp
)



############################################################
# Create a library
############################################################

#Generate the static library from the library sources ### inja ye liberary be project 'hello_library_esme_project_ast' ezafe mikonad
add_library(Name_library STATIC  

	src/focal_sum_gdal.cpp
	
)


target_include_directories(Name_library     
    PUBLIC                                                   
        ${PROJECT_SOURCE_DIR}/include
)




# find system installed GDAL package with predefined CMake variable for finding GDAL
find_package(GDAL REQUIRED)

#find_package(Boost REQUIRED)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

#find_package(Boost 1.68 REQUIRED)
#add_executable(foo foo.cpp)
#target_link_libraries(foo PUBLIC Boost::boost)

    
# Specify location of GDAL header files
include_directories(  

${GDAL_INCLUDE_DIRS}

#${Boost_INCLUDE_DIR}

)

#INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

    
# Specify GDAL libraries to link your cpp executable target against
target_link_libraries(${PROJECT_NAME} 

Name_library 

${GDAL_LIBRARIES}

${Boost_PROGRAM_OPTIONS_LIBRARY}

${Boost_LIBRARIES} 

)


# enable testing functionality
enable_testing()
# testing binary
add_executable(Name_test 

src/test.cpp)

#target_link_libraries(cpp_test PRIVATE sum_integers)
# define tests
add_test(
  NAME Name_add_test
  COMMAND $<TARGET_FILE:Name_test>
  )


