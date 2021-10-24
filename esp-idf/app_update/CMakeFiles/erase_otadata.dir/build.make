# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/rasheek/.espressif/tools/cmake/3.20.3/bin/cmake

# The command to remove a file.
RM = /home/rasheek/.espressif/tools/cmake/3.20.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1

# Utility rule file for erase_otadata.

# Include any custom commands dependencies for this target.
include esp-idf/app_update/CMakeFiles/erase_otadata.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/app_update/CMakeFiles/erase_otadata.dir/progress.make

esp-idf/app_update/CMakeFiles/erase_otadata: partitions.csv
	cd /home/rasheek/src/Viridian/esp-idf/components/app_update && /home/rasheek/.espressif/tools/cmake/3.20.3/bin/cmake -D IDF_PATH="/home/rasheek/src/Viridian/esp-idf" -D SERIAL_TOOL="python /home/rasheek/src/Viridian/esp-idf/components/app_update/otatool.py" -D SERIAL_TOOL_ARGS="--esptool-args before=default_reset after=hard_reset --partition-table-file /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/partitions.csv --partition-table-offset 0x8000 erase_otadata" -D WORKING_DIRECTORY="/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1" -P /home/rasheek/src/Viridian/esp-idf/components/esptool_py/run_serial_tool.cmake

erase_otadata: esp-idf/app_update/CMakeFiles/erase_otadata
erase_otadata: esp-idf/app_update/CMakeFiles/erase_otadata.dir/build.make
.PHONY : erase_otadata

# Rule to build all files generated by this target.
esp-idf/app_update/CMakeFiles/erase_otadata.dir/build: erase_otadata
.PHONY : esp-idf/app_update/CMakeFiles/erase_otadata.dir/build

esp-idf/app_update/CMakeFiles/erase_otadata.dir/clean:
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/app_update && $(CMAKE_COMMAND) -P CMakeFiles/erase_otadata.dir/cmake_clean.cmake
.PHONY : esp-idf/app_update/CMakeFiles/erase_otadata.dir/clean

esp-idf/app_update/CMakeFiles/erase_otadata.dir/depend:
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 /home/rasheek/src/Viridian/esp-idf/components/app_update /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/app_update /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/app_update/CMakeFiles/erase_otadata.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/app_update/CMakeFiles/erase_otadata.dir/depend
