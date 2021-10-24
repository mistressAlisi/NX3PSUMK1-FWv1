idf_component_register(SRCS "MCP7940.cpp"
  INCLUDE_DIRS "include"
  REQUIRES "arduino")

#add_library(MCP7940 STATIC MCP7940.cpp)

#target_include_directories(json PUBLIC cJSON)
		  # Create and import the library targets
#add_subdirectory(.)

# Publicly link `foo` to `main` component
#target_link_libraries(main PUBLIC MCP7940)
