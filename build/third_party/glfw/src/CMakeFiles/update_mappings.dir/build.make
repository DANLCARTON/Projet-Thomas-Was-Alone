# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_SOURCE_DIR = "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/build"

# Utility rule file for update_mappings.

# Include the progress variables for this target.
include third_party/glfw/src/CMakeFiles/update_mappings.dir/progress.make

third_party/glfw/src/CMakeFiles/update_mappings:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Updating gamepad mappings from upstream repository"
	cd "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/third_party/glfw/src" && /usr/bin/cmake -P "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/third_party/glfw/CMake/GenerateMappings.cmake" mappings.h.in mappings.h

update_mappings: third_party/glfw/src/CMakeFiles/update_mappings
update_mappings: third_party/glfw/src/CMakeFiles/update_mappings.dir/build.make

.PHONY : update_mappings

# Rule to build all files generated by this target.
third_party/glfw/src/CMakeFiles/update_mappings.dir/build: update_mappings

.PHONY : third_party/glfw/src/CMakeFiles/update_mappings.dir/build

third_party/glfw/src/CMakeFiles/update_mappings.dir/clean:
	cd "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/build/third_party/glfw/src" && $(CMAKE_COMMAND) -P CMakeFiles/update_mappings.dir/cmake_clean.cmake
.PHONY : third_party/glfw/src/CMakeFiles/update_mappings.dir/clean

third_party/glfw/src/CMakeFiles/update_mappings.dir/depend:
	cd "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main" "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/third_party/glfw/src" "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/build" "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/build/third_party/glfw/src" "/home/maxime/Documents/IMAC/Projet Thomas Was Alone/OpenGLTemplate-main/build/third_party/glfw/src/CMakeFiles/update_mappings.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : third_party/glfw/src/CMakeFiles/update_mappings.dir/depend

