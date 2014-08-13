# Set variable for the generate sources
set(GENERATE_SRCS ${PROJECT_SOURCE_DIR}/generate.c)
set(GENERATE_OUTPUT ${PROJECT_BINARY_DIR}/generate)
set(VERSION_OUTPUT ${PROJECT_BINARY_DIR}/src/version.h)

# Create command to compile the generate command
add_custom_command(
    OUTPUT ${GENERATE_OUTPUT}
    COMMAND gcc -o ${GENERATE_OUTPUT} ${GENERATE_SRCS}
    )

add_custom_target(generate_version
    COMMAND ${GENERATE_OUTPUT} -M 1 -m 0 -p 0 -a "-beta" > ${VERSION_OUTPUT}
    DEPENDS ${GENERATE_OUTPUT}
    VERBATIM
    )

set(SRCS
main.c
)
add_executable(example ${SRCS})
add_dependencies(example generate_version)
