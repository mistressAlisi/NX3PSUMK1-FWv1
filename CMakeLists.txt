# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(d9-NX3PDU-MK3-FWMK1)

# Include Fetchcontent and Nhlomann's Brilliant ModernJSON Library:
include(FetchContent)
set(FETCHCONTENT_BASE_DIR "libraries/")
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.10.2)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
FetchContent_MakeAvailable(json)
target_link_libraries(${project_elf} nlohmann_json::nlohmann_json)
target_include_directories(${project_elf} PRIVATE ${json_SOURCE_DIR}+"/include/nlohmann")