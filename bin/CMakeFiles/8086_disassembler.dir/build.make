# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/pyw/Documents/GitHub/performance_programming_practice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/pyw/Documents/GitHub/performance_programming_practice/bin

# Include any dependencies generated for this target.
include CMakeFiles/8086_disassembler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/8086_disassembler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/8086_disassembler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/8086_disassembler.dir/flags.make

CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o: CMakeFiles/8086_disassembler.dir/flags.make
CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o: /Users/pyw/Documents/GitHub/performance_programming_practice/src/8086_disassembler.c
CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o: CMakeFiles/8086_disassembler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/pyw/Documents/GitHub/performance_programming_practice/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o -MF CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o.d -o CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o -c /Users/pyw/Documents/GitHub/performance_programming_practice/src/8086_disassembler.c

CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/pyw/Documents/GitHub/performance_programming_practice/src/8086_disassembler.c > CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.i

CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/pyw/Documents/GitHub/performance_programming_practice/src/8086_disassembler.c -o CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.s

# Object files for target 8086_disassembler
8086_disassembler_OBJECTS = \
"CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o"

# External object files for target 8086_disassembler
8086_disassembler_EXTERNAL_OBJECTS =

8086_disassembler: CMakeFiles/8086_disassembler.dir/src/8086_disassembler.c.o
8086_disassembler: CMakeFiles/8086_disassembler.dir/build.make
8086_disassembler: CMakeFiles/8086_disassembler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/pyw/Documents/GitHub/performance_programming_practice/bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 8086_disassembler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/8086_disassembler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/8086_disassembler.dir/build: 8086_disassembler
.PHONY : CMakeFiles/8086_disassembler.dir/build

CMakeFiles/8086_disassembler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/8086_disassembler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/8086_disassembler.dir/clean

CMakeFiles/8086_disassembler.dir/depend:
	cd /Users/pyw/Documents/GitHub/performance_programming_practice/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/pyw/Documents/GitHub/performance_programming_practice /Users/pyw/Documents/GitHub/performance_programming_practice /Users/pyw/Documents/GitHub/performance_programming_practice/bin /Users/pyw/Documents/GitHub/performance_programming_practice/bin /Users/pyw/Documents/GitHub/performance_programming_practice/bin/CMakeFiles/8086_disassembler.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/8086_disassembler.dir/depend

