# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum

# Include any dependencies generated for this target.
include source/focal_operation/CMakeFiles/focal_sum.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include source/focal_operation/CMakeFiles/focal_sum.dir/compiler_depend.make

# Include the progress variables for this target.
include source/focal_operation/CMakeFiles/focal_sum.dir/progress.make

# Include the compile flags for this target's objects.
include source/focal_operation/CMakeFiles/focal_sum.dir/flags.make

source/focal_operation/CMakeFiles/focal_sum.dir/source/main_sum.cpp.o: source/focal_operation/CMakeFiles/focal_sum.dir/flags.make
source/focal_operation/CMakeFiles/focal_sum.dir/source/main_sum.cpp.o: source/focal_operation/source/main_sum.cpp
source/focal_operation/CMakeFiles/focal_sum.dir/source/main_sum.cpp.o: source/focal_operation/CMakeFiles/focal_sum.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object source/focal_operation/CMakeFiles/focal_sum.dir/source/main_sum.cpp.o"
	cd /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT source/focal_operation/CMakeFiles/focal_sum.dir/source/main_sum.cpp.o -MF CMakeFiles/focal_sum.dir/source/main_sum.cpp.o.d -o CMakeFiles/focal_sum.dir/source/main_sum.cpp.o -c /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation/source/main_sum.cpp

source/focal_operation/CMakeFiles/focal_sum.dir/source/main_sum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/focal_sum.dir/source/main_sum.cpp.i"
	cd /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation/source/main_sum.cpp > CMakeFiles/focal_sum.dir/source/main_sum.cpp.i

source/focal_operation/CMakeFiles/focal_sum.dir/source/main_sum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/focal_sum.dir/source/main_sum.cpp.s"
	cd /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation/source/main_sum.cpp -o CMakeFiles/focal_sum.dir/source/main_sum.cpp.s

# Object files for target focal_sum
focal_sum_OBJECTS = \
"CMakeFiles/focal_sum.dir/source/main_sum.cpp.o"

# External object files for target focal_sum
focal_sum_EXTERNAL_OBJECTS =

bin/focal_sum: source/focal_operation/CMakeFiles/focal_sum.dir/source/main_sum.cpp.o
bin/focal_sum: source/focal_operation/CMakeFiles/focal_sum.dir/build.make
bin/focal_sum: lib/libio.a
bin/focal_sum: lib/libfocal_operation.a
bin/focal_sum: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.74.0
bin/focal_sum: /usr/lib/libgdal.so
bin/focal_sum: lib/libraster.a
bin/focal_sum: source/focal_operation/CMakeFiles/focal_sum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/focal_sum"
	cd /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/focal_sum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
source/focal_operation/CMakeFiles/focal_sum.dir/build: bin/focal_sum
.PHONY : source/focal_operation/CMakeFiles/focal_sum.dir/build

source/focal_operation/CMakeFiles/focal_sum.dir/clean:
	cd /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation && $(CMAKE_COMMAND) -P CMakeFiles/focal_sum.dir/cmake_clean.cmake
.PHONY : source/focal_operation/CMakeFiles/focal_sum.dir/clean

source/focal_operation/CMakeFiles/focal_sum.dir/depend:
	cd /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation /home/saeb/focal_sum_project/test_GDAL_and_command_line_argument/20240119_focal_sum/source/focal_operation/CMakeFiles/focal_sum.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : source/focal_operation/CMakeFiles/focal_sum.dir/depend

