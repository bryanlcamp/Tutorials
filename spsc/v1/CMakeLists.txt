# Add the source files and set the executable name
add_executable(tutorial_spsc_v1 tutorial_spsc_v1.cpp)

# Set the output directory for this specific target
set_target_properties(tutorial_spsc_v1 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Add any required include directories
target_include_directories(tutorial_spsc_v1 PRIVATE ${CMAKE_SOURCE_DIR}/spsc/v1)

# If there are any libraries you need to link, use target_link_libraries here
# target_link_libraries(tutorial_spsc_v1 your_library)