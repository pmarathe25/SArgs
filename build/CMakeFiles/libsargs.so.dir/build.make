# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pranav/C++/Stealth/SArgs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pranav/C++/Stealth/SArgs/build

# Include any dependencies generated for this target.
include CMakeFiles/libsargs.so.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/libsargs.so.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/libsargs.so.dir/flags.make

CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.o: CMakeFiles/libsargs.so.dir/flags.make
CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.o: ../src/ArgumentParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pranav/C++/Stealth/SArgs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.o -c /home/pranav/C++/Stealth/SArgs/src/ArgumentParser.cpp

CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pranav/C++/Stealth/SArgs/src/ArgumentParser.cpp > CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.i

CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pranav/C++/Stealth/SArgs/src/ArgumentParser.cpp -o CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.s

# Object files for target libsargs.so
libsargs_so_OBJECTS = \
"CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.o"

# External object files for target libsargs.so
libsargs_so_EXTERNAL_OBJECTS =

liblibsargs.so.a: CMakeFiles/libsargs.so.dir/src/ArgumentParser.cpp.o
liblibsargs.so.a: CMakeFiles/libsargs.so.dir/build.make
liblibsargs.so.a: CMakeFiles/libsargs.so.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pranav/C++/Stealth/SArgs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library liblibsargs.so.a"
	$(CMAKE_COMMAND) -P CMakeFiles/libsargs.so.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libsargs.so.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/libsargs.so.dir/build: liblibsargs.so.a

.PHONY : CMakeFiles/libsargs.so.dir/build

CMakeFiles/libsargs.so.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/libsargs.so.dir/cmake_clean.cmake
.PHONY : CMakeFiles/libsargs.so.dir/clean

CMakeFiles/libsargs.so.dir/depend:
	cd /home/pranav/C++/Stealth/SArgs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pranav/C++/Stealth/SArgs /home/pranav/C++/Stealth/SArgs /home/pranav/C++/Stealth/SArgs/build /home/pranav/C++/Stealth/SArgs/build /home/pranav/C++/Stealth/SArgs/build/CMakeFiles/libsargs.so.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/libsargs.so.dir/depend
