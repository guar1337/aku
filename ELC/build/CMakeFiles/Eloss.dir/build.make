# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/zalewski/aku/wrk/ELC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zalewski/aku/wrk/ELC/build

# Include any dependencies generated for this target.
include CMakeFiles/Eloss.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Eloss.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Eloss.dir/flags.make

CMakeFiles/Eloss.dir/ELOSS.f90.o: CMakeFiles/Eloss.dir/flags.make
CMakeFiles/Eloss.dir/ELOSS.f90.o: ../ELOSS.f90
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zalewski/aku/wrk/ELC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building Fortran object CMakeFiles/Eloss.dir/ELOSS.f90.o"
	/usr/bin/f95 $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -c /home/zalewski/aku/wrk/ELC/ELOSS.f90 -o CMakeFiles/Eloss.dir/ELOSS.f90.o

CMakeFiles/Eloss.dir/ELOSS.f90.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/Eloss.dir/ELOSS.f90.i"
	/usr/bin/f95 $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -E /home/zalewski/aku/wrk/ELC/ELOSS.f90 > CMakeFiles/Eloss.dir/ELOSS.f90.i

CMakeFiles/Eloss.dir/ELOSS.f90.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/Eloss.dir/ELOSS.f90.s"
	/usr/bin/f95 $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -S /home/zalewski/aku/wrk/ELC/ELOSS.f90 -o CMakeFiles/Eloss.dir/ELOSS.f90.s

CMakeFiles/Eloss.dir/ELOSS.f90.o.requires:

.PHONY : CMakeFiles/Eloss.dir/ELOSS.f90.o.requires

CMakeFiles/Eloss.dir/ELOSS.f90.o.provides: CMakeFiles/Eloss.dir/ELOSS.f90.o.requires
	$(MAKE) -f CMakeFiles/Eloss.dir/build.make CMakeFiles/Eloss.dir/ELOSS.f90.o.provides.build
.PHONY : CMakeFiles/Eloss.dir/ELOSS.f90.o.provides

CMakeFiles/Eloss.dir/ELOSS.f90.o.provides.build: CMakeFiles/Eloss.dir/ELOSS.f90.o


CMakeFiles/Eloss.dir/ELC.cpp.o: CMakeFiles/Eloss.dir/flags.make
CMakeFiles/Eloss.dir/ELC.cpp.o: ../ELC.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zalewski/aku/wrk/ELC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Eloss.dir/ELC.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Eloss.dir/ELC.cpp.o -c /home/zalewski/aku/wrk/ELC/ELC.cpp

CMakeFiles/Eloss.dir/ELC.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Eloss.dir/ELC.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zalewski/aku/wrk/ELC/ELC.cpp > CMakeFiles/Eloss.dir/ELC.cpp.i

CMakeFiles/Eloss.dir/ELC.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Eloss.dir/ELC.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zalewski/aku/wrk/ELC/ELC.cpp -o CMakeFiles/Eloss.dir/ELC.cpp.s

CMakeFiles/Eloss.dir/ELC.cpp.o.requires:

.PHONY : CMakeFiles/Eloss.dir/ELC.cpp.o.requires

CMakeFiles/Eloss.dir/ELC.cpp.o.provides: CMakeFiles/Eloss.dir/ELC.cpp.o.requires
	$(MAKE) -f CMakeFiles/Eloss.dir/build.make CMakeFiles/Eloss.dir/ELC.cpp.o.provides.build
.PHONY : CMakeFiles/Eloss.dir/ELC.cpp.o.provides

CMakeFiles/Eloss.dir/ELC.cpp.o.provides.build: CMakeFiles/Eloss.dir/ELC.cpp.o


CMakeFiles/Eloss.dir/AELC.cpp.o: CMakeFiles/Eloss.dir/flags.make
CMakeFiles/Eloss.dir/AELC.cpp.o: ../AELC.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zalewski/aku/wrk/ELC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Eloss.dir/AELC.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Eloss.dir/AELC.cpp.o -c /home/zalewski/aku/wrk/ELC/AELC.cpp

CMakeFiles/Eloss.dir/AELC.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Eloss.dir/AELC.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zalewski/aku/wrk/ELC/AELC.cpp > CMakeFiles/Eloss.dir/AELC.cpp.i

CMakeFiles/Eloss.dir/AELC.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Eloss.dir/AELC.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zalewski/aku/wrk/ELC/AELC.cpp -o CMakeFiles/Eloss.dir/AELC.cpp.s

CMakeFiles/Eloss.dir/AELC.cpp.o.requires:

.PHONY : CMakeFiles/Eloss.dir/AELC.cpp.o.requires

CMakeFiles/Eloss.dir/AELC.cpp.o.provides: CMakeFiles/Eloss.dir/AELC.cpp.o.requires
	$(MAKE) -f CMakeFiles/Eloss.dir/build.make CMakeFiles/Eloss.dir/AELC.cpp.o.provides.build
.PHONY : CMakeFiles/Eloss.dir/AELC.cpp.o.provides

CMakeFiles/Eloss.dir/AELC.cpp.o.provides.build: CMakeFiles/Eloss.dir/AELC.cpp.o


# Object files for target Eloss
Eloss_OBJECTS = \
"CMakeFiles/Eloss.dir/ELOSS.f90.o" \
"CMakeFiles/Eloss.dir/ELC.cpp.o" \
"CMakeFiles/Eloss.dir/AELC.cpp.o"

# External object files for target Eloss
Eloss_EXTERNAL_OBJECTS =

libEloss.so: CMakeFiles/Eloss.dir/ELOSS.f90.o
libEloss.so: CMakeFiles/Eloss.dir/ELC.cpp.o
libEloss.so: CMakeFiles/Eloss.dir/AELC.cpp.o
libEloss.so: CMakeFiles/Eloss.dir/build.make
libEloss.so: /usr/lib/x86_64-linux-gnu/libgsl.so
libEloss.so: /usr/lib/x86_64-linux-gnu/libgslcblas.so
libEloss.so: /usr/local/lib/libCore.so
libEloss.so: /usr/local/lib/libImt.so
libEloss.so: /usr/local/lib/libRIO.so
libEloss.so: /usr/local/lib/libNet.so
libEloss.so: /usr/local/lib/libHist.so
libEloss.so: /usr/local/lib/libGraf.so
libEloss.so: /usr/local/lib/libGraf3d.so
libEloss.so: /usr/local/lib/libGpad.so
libEloss.so: /usr/local/lib/libROOTDataFrame.so
libEloss.so: /usr/local/lib/libTree.so
libEloss.so: /usr/local/lib/libTreePlayer.so
libEloss.so: /usr/local/lib/libRint.so
libEloss.so: /usr/local/lib/libPostscript.so
libEloss.so: /usr/local/lib/libMatrix.so
libEloss.so: /usr/local/lib/libPhysics.so
libEloss.so: /usr/local/lib/libMathCore.so
libEloss.so: /usr/local/lib/libThread.so
libEloss.so: /usr/local/lib/libMultiProc.so
libEloss.so: CMakeFiles/Eloss.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zalewski/aku/wrk/ELC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library libEloss.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Eloss.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Eloss.dir/build: libEloss.so

.PHONY : CMakeFiles/Eloss.dir/build

CMakeFiles/Eloss.dir/requires: CMakeFiles/Eloss.dir/ELOSS.f90.o.requires
CMakeFiles/Eloss.dir/requires: CMakeFiles/Eloss.dir/ELC.cpp.o.requires
CMakeFiles/Eloss.dir/requires: CMakeFiles/Eloss.dir/AELC.cpp.o.requires

.PHONY : CMakeFiles/Eloss.dir/requires

CMakeFiles/Eloss.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Eloss.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Eloss.dir/clean

CMakeFiles/Eloss.dir/depend:
	cd /home/zalewski/aku/wrk/ELC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zalewski/aku/wrk/ELC /home/zalewski/aku/wrk/ELC /home/zalewski/aku/wrk/ELC/build /home/zalewski/aku/wrk/ELC/build /home/zalewski/aku/wrk/ELC/build/CMakeFiles/Eloss.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Eloss.dir/depend

