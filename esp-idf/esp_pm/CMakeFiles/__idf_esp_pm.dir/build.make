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
include esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/flags.make

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/flags.make
esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj: /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_locks.c
esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj -MF CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj.d -o CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj -c /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_locks.c

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_locks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_pm.dir/pm_locks.c.i"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_locks.c > CMakeFiles/__idf_esp_pm.dir/pm_locks.c.i

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_locks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_pm.dir/pm_locks.c.s"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_locks.c -o CMakeFiles/__idf_esp_pm.dir/pm_locks.c.s

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/flags.make
esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj: /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_trace.c
esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj -MF CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj.d -o CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj -c /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_trace.c

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_trace.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_pm.dir/pm_trace.c.i"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_trace.c > CMakeFiles/__idf_esp_pm.dir/pm_trace.c.i

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_trace.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_pm.dir/pm_trace.c.s"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_trace.c -o CMakeFiles/__idf_esp_pm.dir/pm_trace.c.s

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/flags.make
esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj: /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_impl.c
esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj -MF CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj.d -o CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj -c /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_impl.c

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_impl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_pm.dir/pm_impl.c.i"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_impl.c > CMakeFiles/__idf_esp_pm.dir/pm_impl.c.i

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_impl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_pm.dir/pm_impl.c.s"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rasheek/src/Viridian/esp-idf/components/esp_pm/pm_impl.c -o CMakeFiles/__idf_esp_pm.dir/pm_impl.c.s

# Object files for target __idf_esp_pm
__idf_esp_pm_OBJECTS = \
"CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj" \
"CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj" \
"CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj"

# External object files for target __idf_esp_pm
__idf_esp_pm_EXTERNAL_OBJECTS =

esp-idf/esp_pm/libesp_pm.a: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_locks.c.obj
esp-idf/esp_pm/libesp_pm.a: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_trace.c.obj
esp-idf/esp_pm/libesp_pm.a: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/pm_impl.c.obj
esp-idf/esp_pm/libesp_pm.a: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/build.make
esp-idf/esp_pm/libesp_pm.a: esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libesp_pm.a"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_pm.dir/cmake_clean_target.cmake
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_esp_pm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/build: esp-idf/esp_pm/libesp_pm.a
.PHONY : esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/build

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/clean:
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_pm.dir/cmake_clean.cmake
.PHONY : esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/clean

esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/depend:
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 /home/rasheek/src/Viridian/esp-idf/components/esp_pm /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/esp_pm/CMakeFiles/__idf_esp_pm.dir/depend

