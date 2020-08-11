cmake_minimum_required(VERSION 2.8.5)
project(example)

include_directories(${PROJECT_SOURCE_DIR}/src)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_program(PipEnv pipenv REQUIRED)

# Create command to compile the generate command
add_custom_command(
    OUTPUT
        ${CMAKE_SOURCE_DIR}/generate.py
    COMMAND ${PipEnv} install
    COMMENT "Installing pipenv dependencies [${PipEnv} install]"
    DEPENDS
        ${CMAKE_SOURCE_DIR}/generate.py
        ${CMAKE_SOURCE_DIR}/Pipfile
)

add_custom_target(
    generate_version
    COMMAND ${PipEnv} run ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/generate.py -o src/version.h config.json
    COMMENT "Generating version header [${PipEnv} run ${CMAKE_SOURCE_DIR}/generate.py -o src/version.h config.json]"
    DEPENDS
        ${CMAKE_SOURCE_DIR}/generate.py
        ${CMAKE_SOURCE_DIR}/config.json
)

add_subdirectory(src)
