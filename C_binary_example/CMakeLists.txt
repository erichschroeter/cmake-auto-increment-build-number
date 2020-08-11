cmake_minimum_required(VERSION 2.8.5)
project(example)

include_directories(${PROJECT_BINARY_DIR}/src)

# Set variable for the generate sources
set(GENERATE_SRCS ${PROJECT_SOURCE_DIR}/generate.c)
set(GENERATE_OUTPUT ${PROJECT_BINARY_DIR}/generate)
set(VERSION_OUTPUT ${PROJECT_BINARY_DIR}/src/version.h)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_META "-alpha")

# Create command to compile the generate command
add_custom_command(
    OUTPUT ${GENERATE_OUTPUT}
    COMMAND gcc -o ${GENERATE_OUTPUT} ${GENERATE_SRCS}
    DEPENDS ${GENERATE_SRCS}
    )

add_custom_target(generate_version
    COMMAND ${GENERATE_OUTPUT}
        -M ${VERSION_MAJOR}
	-m ${VERSION_MINOR}
	-p ${VERSION_PATCH}
	-a "${VERSION_META}"
	-F "${PROJECT_BINARY_DIR}/buildnumber"
	-i
	> ${VERSION_OUTPUT}
    DEPENDS ${GENERATE_OUTPUT}
    VERBATIM
    )

add_subdirectory(src)
