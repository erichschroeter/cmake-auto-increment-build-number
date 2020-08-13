cmake_minimum_required(VERSION 2.8.5)
project(example)

include_directories(${PROJECT_SOURCE_DIR}/src)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_program(PipEnv pipenv REQUIRED)

# Create command to install the generate.py dependencies.
add_custom_command(
    OUTPUT
        Pipfile.lock
    COMMAND ${PipEnv} install
    COMMENT "Installing pipenv dependencies [${PipEnv} install]"
    DEPENDS
        Pipfile
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    generate_version
    COMMAND ${PipEnv} run ${Python3_EXECUTABLE} generate.py -o src/version.h config.json
    COMMENT "Generating version header [${PipEnv} run ${CMAKE_CURRENT_SOURCE_DIR}/generate.py -o src/version.h config.json]"
    DEPENDS
        Pipfile.lock
        generate.py
        config.json
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(src)
