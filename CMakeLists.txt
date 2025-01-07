cmake_minimum_required(VERSION 3.20)
project(Theory_of_Computing C)  # Keep the project name if you want

set(CMAKE_C_STANDARD 11)

# Find all source files in the 1.1 directory
file(GLOB SOURCES "1.1/*.c")

# Create separate executables for each source file
foreach(SOURCE ${SOURCES})
    # Extract the filename without extension
    get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)

    # Add the executable target
    add_executable(${EXECUTABLE_NAME} ${SOURCE})

    # Optional: Set the output directory for each executable
    set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endforeach()