# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16

# Include any dependencies generated for this target.
include CMakeFiles/maze.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/maze.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/maze.dir/flags.make

CMakeFiles/maze.dir/maze.c.o: CMakeFiles/maze.dir/flags.make
CMakeFiles/maze.dir/maze.c.o: maze.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/maze.dir/maze.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/maze.dir/maze.c.o   -c /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16/maze.c

CMakeFiles/maze.dir/maze.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/maze.dir/maze.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16/maze.c > CMakeFiles/maze.dir/maze.c.i

CMakeFiles/maze.dir/maze.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/maze.dir/maze.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16/maze.c -o CMakeFiles/maze.dir/maze.c.s

# Object files for target maze
maze_OBJECTS = \
"CMakeFiles/maze.dir/maze.c.o"

# External object files for target maze
maze_EXTERNAL_OBJECTS =

maze: CMakeFiles/maze.dir/maze.c.o
maze: CMakeFiles/maze.dir/build.make
maze: CMakeFiles/maze.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable maze"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maze.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/maze.dir/build: maze

.PHONY : CMakeFiles/maze.dir/build

CMakeFiles/maze.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/maze.dir/cmake_clean.cmake
.PHONY : CMakeFiles/maze.dir/clean

CMakeFiles/maze.dir/depend:
	cd /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16 /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16 /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16 /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16 /Users/aclake/luc/comp310/homework-1-maze-shortest-paths-alake16/CMakeFiles/maze.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/maze.dir/depend
