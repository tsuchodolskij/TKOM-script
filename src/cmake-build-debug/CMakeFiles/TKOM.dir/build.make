# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /opt/clion-2019.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2019.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tomas/TKOM/TKOM-script/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tomas/TKOM/TKOM-script/src/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TKOM.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TKOM.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TKOM.dir/flags.make

CMakeFiles/TKOM.dir/main.cpp.o: CMakeFiles/TKOM.dir/flags.make
CMakeFiles/TKOM.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/TKOM/TKOM-script/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TKOM.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TKOM.dir/main.cpp.o -c /home/tomas/TKOM/TKOM-script/src/main.cpp

CMakeFiles/TKOM.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TKOM.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomas/TKOM/TKOM-script/src/main.cpp > CMakeFiles/TKOM.dir/main.cpp.i

CMakeFiles/TKOM.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TKOM.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomas/TKOM/TKOM-script/src/main.cpp -o CMakeFiles/TKOM.dir/main.cpp.s

CMakeFiles/TKOM.dir/lexer.cpp.o: CMakeFiles/TKOM.dir/flags.make
CMakeFiles/TKOM.dir/lexer.cpp.o: ../lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/TKOM/TKOM-script/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TKOM.dir/lexer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TKOM.dir/lexer.cpp.o -c /home/tomas/TKOM/TKOM-script/src/lexer.cpp

CMakeFiles/TKOM.dir/lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TKOM.dir/lexer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomas/TKOM/TKOM-script/src/lexer.cpp > CMakeFiles/TKOM.dir/lexer.cpp.i

CMakeFiles/TKOM.dir/lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TKOM.dir/lexer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomas/TKOM/TKOM-script/src/lexer.cpp -o CMakeFiles/TKOM.dir/lexer.cpp.s

CMakeFiles/TKOM.dir/source.cpp.o: CMakeFiles/TKOM.dir/flags.make
CMakeFiles/TKOM.dir/source.cpp.o: ../source.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/TKOM/TKOM-script/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TKOM.dir/source.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TKOM.dir/source.cpp.o -c /home/tomas/TKOM/TKOM-script/src/source.cpp

CMakeFiles/TKOM.dir/source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TKOM.dir/source.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomas/TKOM/TKOM-script/src/source.cpp > CMakeFiles/TKOM.dir/source.cpp.i

CMakeFiles/TKOM.dir/source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TKOM.dir/source.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomas/TKOM/TKOM-script/src/source.cpp -o CMakeFiles/TKOM.dir/source.cpp.s

CMakeFiles/TKOM.dir/token.cpp.o: CMakeFiles/TKOM.dir/flags.make
CMakeFiles/TKOM.dir/token.cpp.o: ../token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tomas/TKOM/TKOM-script/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TKOM.dir/token.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TKOM.dir/token.cpp.o -c /home/tomas/TKOM/TKOM-script/src/token.cpp

CMakeFiles/TKOM.dir/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TKOM.dir/token.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tomas/TKOM/TKOM-script/src/token.cpp > CMakeFiles/TKOM.dir/token.cpp.i

CMakeFiles/TKOM.dir/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TKOM.dir/token.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tomas/TKOM/TKOM-script/src/token.cpp -o CMakeFiles/TKOM.dir/token.cpp.s

# Object files for target TKOM
TKOM_OBJECTS = \
"CMakeFiles/TKOM.dir/main.cpp.o" \
"CMakeFiles/TKOM.dir/lexer.cpp.o" \
"CMakeFiles/TKOM.dir/source.cpp.o" \
"CMakeFiles/TKOM.dir/token.cpp.o"

# External object files for target TKOM
TKOM_EXTERNAL_OBJECTS =

TKOM: CMakeFiles/TKOM.dir/main.cpp.o
TKOM: CMakeFiles/TKOM.dir/lexer.cpp.o
TKOM: CMakeFiles/TKOM.dir/source.cpp.o
TKOM: CMakeFiles/TKOM.dir/token.cpp.o
TKOM: CMakeFiles/TKOM.dir/build.make
TKOM: CMakeFiles/TKOM.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tomas/TKOM/TKOM-script/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable TKOM"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TKOM.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TKOM.dir/build: TKOM

.PHONY : CMakeFiles/TKOM.dir/build

CMakeFiles/TKOM.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TKOM.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TKOM.dir/clean

CMakeFiles/TKOM.dir/depend:
	cd /home/tomas/TKOM/TKOM-script/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tomas/TKOM/TKOM-script/src /home/tomas/TKOM/TKOM-script/src /home/tomas/TKOM/TKOM-script/src/cmake-build-debug /home/tomas/TKOM/TKOM-script/src/cmake-build-debug /home/tomas/TKOM/TKOM-script/src/cmake-build-debug/CMakeFiles/TKOM.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TKOM.dir/depend

