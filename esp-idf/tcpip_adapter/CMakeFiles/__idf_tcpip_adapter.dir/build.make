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

# Include any dependencies generated for this target.
include esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/flags.make

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/flags.make
esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj: /home/rasheek/src/Viridian/esp-idf/components/tcpip_adapter/tcpip_adapter_compat.c
esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/tcpip_adapter && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj -MF CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj.d -o CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj -c /home/rasheek/src/Viridian/esp-idf/components/tcpip_adapter/tcpip_adapter_compat.c

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.i"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/tcpip_adapter && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rasheek/src/Viridian/esp-idf/components/tcpip_adapter/tcpip_adapter_compat.c > CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.i

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.s"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/tcpip_adapter && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rasheek/src/Viridian/esp-idf/components/tcpip_adapter/tcpip_adapter_compat.c -o CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.s

# Object files for target __idf_tcpip_adapter
__idf_tcpip_adapter_OBJECTS = \
"CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj"

# External object files for target __idf_tcpip_adapter
__idf_tcpip_adapter_EXTERNAL_OBJECTS =

esp-idf/tcpip_adapter/libtcpip_adapter.a: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/tcpip_adapter_compat.c.obj
esp-idf/tcpip_adapter/libtcpip_adapter.a: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/build.make
esp-idf/tcpip_adapter/libtcpip_adapter.a: esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libtcpip_adapter.a"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/tcpip_adapter && $(CMAKE_COMMAND) -P CMakeFiles/__idf_tcpip_adapter.dir/cmake_clean_target.cmake
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/tcpip_adapter && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_tcpip_adapter.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/build: esp-idf/tcpip_adapter/libtcpip_adapter.a
.PHONY : esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/build

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/clean:
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/tcpip_adapter && $(CMAKE_COMMAND) -P CMakeFiles/__idf_tcpip_adapter.dir/cmake_clean.cmake
.PHONY : esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/clean

esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/depend:
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 /home/rasheek/src/Viridian/esp-idf/components/tcpip_adapter /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/tcpip_adapter /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/tcpip_adapter/CMakeFiles/__idf_tcpip_adapter.dir/depend

