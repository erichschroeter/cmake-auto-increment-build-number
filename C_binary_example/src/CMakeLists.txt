set(SRCS
main.c
)
add_executable(example ${SRCS})
add_dependencies(example generate_version)
