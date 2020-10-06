cmake_minimum_required(VERSION 2.8.5)
project(example)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_program(PipEnv pipenv REQUIRED)

add_custom_command(
    OUTPUT
        ${PROJECT_SOURCE_DIR}/src/version.h
        ${PROJECT_SOURCE_DIR}/src/version.c
    COMMAND ${PipEnv} run ${Python3_EXECUTABLE} generate.py -o src/ config.json
    COMMENT "Generating version code [${PipEnv} run generate.py -o src/ config.json]"
    DEPENDS
        Pipfile.lock
        generate.py
        config.json
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(
    example
    src/main.c
    src/version.c
)
target_link_libraries(example version)
