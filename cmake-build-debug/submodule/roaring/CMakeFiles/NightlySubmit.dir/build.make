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
CMAKE_COMMAND = /home/giacomo/Scaricati/jetbrains/CLion-2022.1.3/clion-2022.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/giacomo/Scaricati/jetbrains/CLion-2022.1.3/clion-2022.1.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/giacomo/projects/yaucl-graph

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/giacomo/projects/yaucl-graph/cmake-build-debug

# Utility rule file for NightlySubmit.

# Include any custom commands dependencies for this target.
include submodule/roaring/CMakeFiles/NightlySubmit.dir/compiler_depend.make

# Include the progress variables for this target.
include submodule/roaring/CMakeFiles/NightlySubmit.dir/progress.make

submodule/roaring/CMakeFiles/NightlySubmit:
	cd /home/giacomo/projects/yaucl-graph/cmake-build-debug/submodule/roaring && /home/giacomo/Scaricati/jetbrains/CLion-2022.1.3/clion-2022.1.3/bin/cmake/linux/bin/ctest -D NightlySubmit

NightlySubmit: submodule/roaring/CMakeFiles/NightlySubmit
NightlySubmit: submodule/roaring/CMakeFiles/NightlySubmit.dir/build.make
.PHONY : NightlySubmit

# Rule to build all files generated by this target.
submodule/roaring/CMakeFiles/NightlySubmit.dir/build: NightlySubmit
.PHONY : submodule/roaring/CMakeFiles/NightlySubmit.dir/build

submodule/roaring/CMakeFiles/NightlySubmit.dir/clean:
	cd /home/giacomo/projects/yaucl-graph/cmake-build-debug/submodule/roaring && $(CMAKE_COMMAND) -P CMakeFiles/NightlySubmit.dir/cmake_clean.cmake
.PHONY : submodule/roaring/CMakeFiles/NightlySubmit.dir/clean

submodule/roaring/CMakeFiles/NightlySubmit.dir/depend:
	cd /home/giacomo/projects/yaucl-graph/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/giacomo/projects/yaucl-graph /home/giacomo/projects/yaucl-graph/submodule/roaring /home/giacomo/projects/yaucl-graph/cmake-build-debug /home/giacomo/projects/yaucl-graph/cmake-build-debug/submodule/roaring /home/giacomo/projects/yaucl-graph/cmake-build-debug/submodule/roaring/CMakeFiles/NightlySubmit.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : submodule/roaring/CMakeFiles/NightlySubmit.dir/depend

