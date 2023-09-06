cmake_minimum_required(VERSION 3.14)

project(focal_project LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

enable_testing()

add_subdirectory(source)

include(GNUInstallDirs)

install(TARGETS focal_sum DESTINATION ${CMAKE_INSTALL_BINDIR})

find_package(Doxygen REQUIRED)

set(DOXYGEN_GENERATE_HTML YES)

doxygen_add_docs(doc ${PROJECT_SOURCE_DIR})
