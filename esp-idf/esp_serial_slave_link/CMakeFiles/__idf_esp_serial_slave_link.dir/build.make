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
include esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/compiler_depend.make

# Include the progress variables for this target.
include esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/progress.make

# Include the compile flags for this target's objects.
include esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/flags.make

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/flags.make
esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj: /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl.c
esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj -MF CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj.d -o CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj -c /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl.c

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.i"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl.c > CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.i

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.s"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl.c -o CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.s

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/flags.make
esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj: /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl_sdio.c
esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj -MF CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj.d -o CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj -c /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl_sdio.c

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.i"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl_sdio.c > CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.i

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.s"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl_sdio.c -o CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.s

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/flags.make
esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj: /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl_spi.c
esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj -MF CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj.d -o CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj -c /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl_spi.c

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.i"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl_spi.c > CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.i

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.s"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && /home/rasheek/.espressif/tools/xtensa-esp32-elf/esp-2021r1-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link/essl_spi.c -o CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.s

# Object files for target __idf_esp_serial_slave_link
__idf_esp_serial_slave_link_OBJECTS = \
"CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj" \
"CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj" \
"CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj"

# External object files for target __idf_esp_serial_slave_link
__idf_esp_serial_slave_link_EXTERNAL_OBJECTS =

esp-idf/esp_serial_slave_link/libesp_serial_slave_link.a: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl.c.obj
esp-idf/esp_serial_slave_link/libesp_serial_slave_link.a: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_sdio.c.obj
esp-idf/esp_serial_slave_link/libesp_serial_slave_link.a: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/essl_spi.c.obj
esp-idf/esp_serial_slave_link/libesp_serial_slave_link.a: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/build.make
esp-idf/esp_serial_slave_link/libesp_serial_slave_link.a: esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libesp_serial_slave_link.a"
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_serial_slave_link.dir/cmake_clean_target.cmake
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/__idf_esp_serial_slave_link.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/build: esp-idf/esp_serial_slave_link/libesp_serial_slave_link.a
.PHONY : esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/build

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/clean:
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link && $(CMAKE_COMMAND) -P CMakeFiles/__idf_esp_serial_slave_link.dir/cmake_clean.cmake
.PHONY : esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/clean

esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/depend:
	cd /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 /home/rasheek/src/Viridian/esp-idf/components/esp_serial_slave_link /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1 /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link /home/rasheek/src/Viridian/d9-NX3PDU-MK3-FWMK1/esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/esp_serial_slave_link/CMakeFiles/__idf_esp_serial_slave_link.dir/depend

