# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/build

# Include any dependencies generated for this target.
include CMakeFiles/Babel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Babel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Babel.dir/flags.make

CMakeFiles/Babel.dir/src/client/main.cpp.o: CMakeFiles/Babel.dir/flags.make
CMakeFiles/Babel.dir/src/client/main.cpp.o: ../src/client/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Babel.dir/src/client/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Babel.dir/src/client/main.cpp.o -c /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/src/client/main.cpp

CMakeFiles/Babel.dir/src/client/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Babel.dir/src/client/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/src/client/main.cpp > CMakeFiles/Babel.dir/src/client/main.cpp.i

CMakeFiles/Babel.dir/src/client/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Babel.dir/src/client/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/src/client/main.cpp -o CMakeFiles/Babel.dir/src/client/main.cpp.s

# Object files for target Babel
Babel_OBJECTS = \
"CMakeFiles/Babel.dir/src/client/main.cpp.o"

# External object files for target Babel
Babel_EXTERNAL_OBJECTS =

bin/Babel: CMakeFiles/Babel.dir/src/client/main.cpp.o
bin/Babel: CMakeFiles/Babel.dir/build.make
bin/Babel: /home/cyril/.conan/data/qt/5.14.2/bincrafters/stable/package/38e652426dd157c4a4aa966ab7cf60c1fd08960f/lib/libQt5Widgets.so.5.14.2
bin/Babel: /home/cyril/.conan/data/qt/5.14.2/bincrafters/stable/package/38e652426dd157c4a4aa966ab7cf60c1fd08960f/lib/libQt5Gui.so.5.14.2
bin/Babel: /home/cyril/.conan/data/qt/5.14.2/bincrafters/stable/package/38e652426dd157c4a4aa966ab7cf60c1fd08960f/lib/libQt5Core.so.5.14.2
bin/Babel: CMakeFiles/Babel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/Babel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Babel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Babel.dir/build: bin/Babel

.PHONY : CMakeFiles/Babel.dir/build

CMakeFiles/Babel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Babel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Babel.dir/clean

CMakeFiles/Babel.dir/depend:
	cd /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/build /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/build /home/cyril/epitech/Ans3/B-CPP-500-MPL-5-1-babel-yoan.vessiere/build/CMakeFiles/Babel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Babel.dir/depend

