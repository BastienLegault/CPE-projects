# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/build

# Include any dependencies generated for this target.
include CMakeFiles/cpe_surface.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpe_surface.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpe_surface.dir/flags.make

CMakeFiles/cpe_surface.dir/project/main.cc.o: CMakeFiles/cpe_surface.dir/flags.make
CMakeFiles/cpe_surface.dir/project/main.cc.o: ../project/main.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cpe_surface.dir/project/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cpe_surface.dir/project/main.cc.o -c /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/main.cc

CMakeFiles/cpe_surface.dir/project/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpe_surface.dir/project/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/main.cc > CMakeFiles/cpe_surface.dir/project/main.cc.i

CMakeFiles/cpe_surface.dir/project/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpe_surface.dir/project/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/main.cc -o CMakeFiles/cpe_surface.dir/project/main.cc.s

CMakeFiles/cpe_surface.dir/project/main.cc.o.requires:
.PHONY : CMakeFiles/cpe_surface.dir/project/main.cc.o.requires

CMakeFiles/cpe_surface.dir/project/main.cc.o.provides: CMakeFiles/cpe_surface.dir/project/main.cc.o.requires
	$(MAKE) -f CMakeFiles/cpe_surface.dir/build.make CMakeFiles/cpe_surface.dir/project/main.cc.o.provides.build
.PHONY : CMakeFiles/cpe_surface.dir/project/main.cc.o.provides

CMakeFiles/cpe_surface.dir/project/main.cc.o.provides.build: CMakeFiles/cpe_surface.dir/project/main.cc.o

CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o: CMakeFiles/cpe_surface.dir/flags.make
CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o: ../project/gl-utils.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o -c /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/gl-utils.cc

CMakeFiles/cpe_surface.dir/project/gl-utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpe_surface.dir/project/gl-utils.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/gl-utils.cc > CMakeFiles/cpe_surface.dir/project/gl-utils.cc.i

CMakeFiles/cpe_surface.dir/project/gl-utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpe_surface.dir/project/gl-utils.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/gl-utils.cc -o CMakeFiles/cpe_surface.dir/project/gl-utils.cc.s

CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o.requires:
.PHONY : CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o.requires

CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o.provides: CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o.requires
	$(MAKE) -f CMakeFiles/cpe_surface.dir/build.make CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o.provides.build
.PHONY : CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o.provides

CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o.provides.build: CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o

CMakeFiles/cpe_surface.dir/project/tga.cc.o: CMakeFiles/cpe_surface.dir/flags.make
CMakeFiles/cpe_surface.dir/project/tga.cc.o: ../project/tga.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/cpe_surface.dir/project/tga.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/cpe_surface.dir/project/tga.cc.o -c /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/tga.cc

CMakeFiles/cpe_surface.dir/project/tga.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpe_surface.dir/project/tga.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/tga.cc > CMakeFiles/cpe_surface.dir/project/tga.cc.i

CMakeFiles/cpe_surface.dir/project/tga.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpe_surface.dir/project/tga.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/project/tga.cc -o CMakeFiles/cpe_surface.dir/project/tga.cc.s

CMakeFiles/cpe_surface.dir/project/tga.cc.o.requires:
.PHONY : CMakeFiles/cpe_surface.dir/project/tga.cc.o.requires

CMakeFiles/cpe_surface.dir/project/tga.cc.o.provides: CMakeFiles/cpe_surface.dir/project/tga.cc.o.requires
	$(MAKE) -f CMakeFiles/cpe_surface.dir/build.make CMakeFiles/cpe_surface.dir/project/tga.cc.o.provides.build
.PHONY : CMakeFiles/cpe_surface.dir/project/tga.cc.o.provides

CMakeFiles/cpe_surface.dir/project/tga.cc.o.provides.build: CMakeFiles/cpe_surface.dir/project/tga.cc.o

# Object files for target cpe_surface
cpe_surface_OBJECTS = \
"CMakeFiles/cpe_surface.dir/project/main.cc.o" \
"CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o" \
"CMakeFiles/cpe_surface.dir/project/tga.cc.o"

# External object files for target cpe_surface
cpe_surface_EXTERNAL_OBJECTS =

cpe_surface: CMakeFiles/cpe_surface.dir/project/main.cc.o
cpe_surface: CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o
cpe_surface: CMakeFiles/cpe_surface.dir/project/tga.cc.o
cpe_surface: CMakeFiles/cpe_surface.dir/build.make
cpe_surface: /usr/lib/x86_64-linux-gnu/libGLU.so
cpe_surface: /usr/lib/x86_64-linux-gnu/libGL.so
cpe_surface: /usr/lib/x86_64-linux-gnu/libSM.so
cpe_surface: /usr/lib/x86_64-linux-gnu/libICE.so
cpe_surface: /usr/lib/x86_64-linux-gnu/libX11.so
cpe_surface: /usr/lib/x86_64-linux-gnu/libXext.so
cpe_surface: CMakeFiles/cpe_surface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable cpe_surface"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpe_surface.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpe_surface.dir/build: cpe_surface
.PHONY : CMakeFiles/cpe_surface.dir/build

CMakeFiles/cpe_surface.dir/requires: CMakeFiles/cpe_surface.dir/project/main.cc.o.requires
CMakeFiles/cpe_surface.dir/requires: CMakeFiles/cpe_surface.dir/project/gl-utils.cc.o.requires
CMakeFiles/cpe_surface.dir/requires: CMakeFiles/cpe_surface.dir/project/tga.cc.o.requires
.PHONY : CMakeFiles/cpe_surface.dir/requires

CMakeFiles/cpe_surface.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpe_surface.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpe_surface.dir/clean

CMakeFiles/cpe_surface.dir/depend:
	cd /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/build /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/build /fs03/share/users/mathieu.badoux/home/tp_tissus/tp_tissu_gpu/build/CMakeFiles/cpe_surface.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpe_surface.dir/depend

