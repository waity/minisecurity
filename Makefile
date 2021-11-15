# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.21.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.21.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/connor.waity/connor/mini-security

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/connor.waity/connor/mini-security

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.21.4/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.21.4/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/connor.waity/connor/mini-security/CMakeFiles /Users/connor.waity/connor/mini-security//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/connor.waity/connor/mini-security/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named run

# Build rule for target.
run: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 run
.PHONY : run

# fast build rule for target.
run/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/build
.PHONY : run/fast

src/capture.o: src/capture.cpp.o
.PHONY : src/capture.o

# target to build an object file
src/capture.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/capture.cpp.o
.PHONY : src/capture.cpp.o

src/capture.i: src/capture.cpp.i
.PHONY : src/capture.i

# target to preprocess a source file
src/capture.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/capture.cpp.i
.PHONY : src/capture.cpp.i

src/capture.s: src/capture.cpp.s
.PHONY : src/capture.s

# target to generate assembly for a file
src/capture.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/capture.cpp.s
.PHONY : src/capture.cpp.s

src/process.o: src/process.cpp.o
.PHONY : src/process.o

# target to build an object file
src/process.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/process.cpp.o
.PHONY : src/process.cpp.o

src/process.i: src/process.cpp.i
.PHONY : src/process.i

# target to preprocess a source file
src/process.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/process.cpp.i
.PHONY : src/process.cpp.i

src/process.s: src/process.cpp.s
.PHONY : src/process.s

# target to generate assembly for a file
src/process.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/process.cpp.s
.PHONY : src/process.cpp.s

src/run.o: src/run.cpp.o
.PHONY : src/run.o

# target to build an object file
src/run.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/run.cpp.o
.PHONY : src/run.cpp.o

src/run.i: src/run.cpp.i
.PHONY : src/run.i

# target to preprocess a source file
src/run.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/run.cpp.i
.PHONY : src/run.cpp.i

src/run.s: src/run.cpp.s
.PHONY : src/run.s

# target to generate assembly for a file
src/run.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/src/run.cpp.s
.PHONY : src/run.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... run"
	@echo "... src/capture.o"
	@echo "... src/capture.i"
	@echo "... src/capture.s"
	@echo "... src/process.o"
	@echo "... src/process.i"
	@echo "... src/process.s"
	@echo "... src/run.o"
	@echo "... src/run.i"
	@echo "... src/run.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

